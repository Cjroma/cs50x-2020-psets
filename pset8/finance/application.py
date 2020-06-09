import os
import datetime


from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True



# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    session['price'] = None
    session['symbol'] = None
    session['shares'] = None
    session['cost'] = None
    session['company'] = None
    session['cash'] = None
    session['quantity'] = None
    session['transaction'] = None

    userStocks = db.execute("SELECT * FROM userstocks WHERE user_id = ? ORDER BY quantity DESC",
    session["user_id"])

    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    totalTotal = 0
    for stocks in userStocks:

        if stocks:
            result = None;
            result = lookup(stocks['symbol'])

            stocks['cost'] = result['price']
            stocks['total'] = result['price'] * stocks['quantity']
            totalTotal += result['price'] * stocks['quantity']

    return render_template("index.html", userStocks=userStocks, userCash=usd(user[0]['cash']), usd=usd, totalTotal=totalTotal)


# Clear session
@app.route("/reset")
@login_required
def reset():
    session['price'] = None
    session['symbol'] = None
    session['shares'] = None
    session['cost'] = None
    session['company'] = None
    session['cash'] = None
    session['quantity'] = None

    if session['transaction'] == 'sold':
        session['transaction'] = None;
        return redirect("/sell")
    elif session['transaction'] == 'bought':
        session['transaction'] = None;
        return redirect("/buy")
    else:
        session['transaction'] = None;
        return redirect("/")

# Change password
@app.route("/changepass", methods=["GET", "POST"])
@login_required
def changepass():
    if request.method == "POST":
        currentPass = request.form.get("current-pass")
        newPass  = request.form.get("new-pass")
        confirmPass = request.form.get("confirm-pass")

        user = db.execute("SELECT * FROM users WHERE id = ?", session['user_id'])

        # Ensure user to provide required field
        if not currentPass or not newPass or not confirmPass:
            flash("Please provide required field.", 'error')
            return redirect("/changepass")

        # Check if current password is correct
        if not check_password_hash(user[0]['hash'], currentPass):
            flash("Incorrect current password!", 'error')
            return redirect("/changepass")

        # Check if new password is match
        if newPass != confirmPass:
            flash("Password does not match!", 'error')
            return redirect("/changepass")

        # Ensure current password and new password is the same
        if newPass == currentPass:
            flash("Please enter new password that does not match your current password!", 'error')
            return redirect("/changepass")
        if len(newPass) < 6:
            flash("Please enter 6 or more characters!", 'error')
            return redirect("/changepass")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(newPass), session['user_id'])
        flash("Password changed.", 'info')
        return redirect("/")
    return render_template("change_pass.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # Ensure symbol was submitted
        if request.form.get("symbol") == '' and session['symbol'] is None:
            return apology("must provide symbol", 403)

        # Ensure shares was submitted
        if not request.form.get("shares") and session['symbol'] is None:
            return apology("must provide shares", 403)

        if session['symbol'] is None and session['shares'] is None:
            result = None

            # Search for symbol using api
            result = lookup(request.form.get("symbol"))

            # If symbol is invalid or not found in database
            if not result:
                return apology("Invalid Symbol", 403)

            # If shares entered by user is not positive integer
            if int(request.form.get("shares")) < 1:
                return apology("Invalid number of shares", 403)
            user = db.execute("SELECT * FROM users WHERE id=:user_id", user_id = session["user_id"])

            price = result["price"]
            session['transaction'] = 'bought'
            session['price'] = price
            session['symbol'] = result["symbol"]
            session['shares'] = request.form.get("shares")
            session['cost'] = price * int(session['shares'])
            session['company'] = result['name']



            flash(session['shares'])
            flash(session['symbol'])
            flash(usd(price))
            flash(usd(price*int(session['shares'])))
            flash(usd(user[0]['cash']))
            return redirect("/buy")

        # If user confirmed the transaction
        if  session['symbol'] and session['shares']:
            date = datetime.datetime.utcnow()

            user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
            userTransactions = db.execute("SELECT * FROM userstocks WHERE user_id = ? AND symbol = ?",
            session["user_id"], session['symbol'])

            # Render Apology if dont have enough cash
            if session['cost'] > user[0]['cash']:
                session['price'] = None
                session['symbol'] = None
                session['shares'] = None
                session['cost'] = None
                session['company'] = None
                return apology("Not enough cash", 403)

            if userTransactions != []:
                newQty = int(userTransactions[0]['quantity']) + int(session['shares'])
                db.execute("UPDATE userstocks SET quantity = ? WHERE user_id = ? AND symbol = ?",
                newQty, session['user_id'], session['symbol'])
            else:
                newQty = int(session['shares'])
                db.execute("INSERT INTO userstocks (user_id, symbol, company, quantity) VALUES (?, ?, ?, ?)",
                session["user_id"], session['symbol'], session['company'], newQty)

            # Insert date of purchase to database
            typeT = 'bought'
            db.execute("INSERT INTO 'transaction' (user_id, date, symbol, cost, type, shares) VALUES (?, ?, ?, ?, ?, ?)",
            session["user_id"], date.strftime('%Y-%m-%d %H:%M:%S'), session['symbol'], session['price'], typeT, session['shares'])

            # Update user cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?",
            (user[0]['cash'] - session["cost"]), session['user_id'])

            # Inform the user that transaction was successful!
            flash("Success!", "success")
            flash(usd(session['cost']), 'red')
            return redirect("/")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT * FROM 'transaction' WHERE user_id = ? ORDER BY date DESC", session['user_id'])

    for transaction in transactions:
        date = datetime.datetime.strptime(transaction['date'], '%Y-%m-%d %H:%M:%S')
        transaction['date'] = date.strftime('%b %d %Y %H:%M:%S')
    return render_template("history.html", usd=usd, transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]


        flash("Logged in Successfully!", "info")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    # Forget any user_id
    session.clear()


    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        result = None;
        result = lookup(request.form.get("symbol"))

        if not result:
            return apology("Invalid Symbol", 403)

        company = result["name"]
        price = result["price"]
        symbol = result["symbol"]

        flash(f"A share of {company} ({symbol}) costs {usd(price)}")

        return redirect("/quote")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password");
        confirmPass = request.form.get("confirmation")

        user = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure user entered 6 or more character
        if len(username) < 6 or len(password) < 6:
            flash("Please enter 6 or more character for username and password.", "error")
            return redirect("/register")

        # Check if username is already taken
        if len(user) == 1:
            return apology("Username is already taken!", 403)

        # Check if password entered does not match
        if password != confirmPass:
            return apology("Password does not match!", 403)

        # Insert user to database
        db.execute("INSERT INTO users ('username', 'hash') VALUES (?, ?)",
        request.form.get("username"), generate_password_hash(request.form.get("password")))


        # Query database for username
        login = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Log user in after registration
        session["user_id"] = login[0]["id"]

        #Inform user that registration has been successful
        flash("Registered Successfully!", "info")

        # Redirect user to home page

        return redirect("/")

    # Return this if method is GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    userStocks = db.execute("SELECT * FROM userstocks WHERE user_id = ? ORDER BY symbol", session['user_id'])

    if request.method == "POST":

        if session['transaction'] == 'sold':

            date = datetime.datetime.utcnow()

            # Record transaction to database
            db.execute("INSERT INTO 'transaction' (user_id, date, symbol, cost, type, shares) VALUES (?, ?, ?, ?, ?, ?)",
            session['user_id'], date.strftime('%Y-%m-%d %H:%M:%S'), session['symbol'], session['price'], 'sold', session['shares'])

            # Update userstocks
            if session['shares'] - session['quantity'] == 0:
                db.execute("DELETE FROM 'userstocks' WHERE symbol = ? and user_id = ?", session['symbol'], session['user_id'])
            else:
                db.execute("UPDATE 'userstocks' SET quantity = ? WHERE user_id = ? AND symbol = ?",
                (session['quantity'] - session['shares']), session['user_id'], session['symbol'])

            # Update user cash
            db.execute("UPDATE 'users' SET cash = ? WHERE id = ?",
            (session['cash'] + session['cost']), session['user_id'])

            flash("Success!", "success")
            flash(usd(session['cost']), 'blue')
            return redirect("/")

        symbol = request.form.get('symbol')

        sharesToSell = int(request.form.get('shares')) if request.form.get('shares') else request.form.get('shares')

        user = db.execute("SELECT * FROM users WHERE id = ?", session['user_id'])

        userStocks = db.execute("SELECT * FROM userstocks WHERE symbol = ? AND user_id = ?",
        symbol, session['user_id'])

        sharesInAcc = userStocks[0]['quantity'] if userStocks else 0

        # Ensure symbol was submitted
        if symbol == '':
            return apology("must provide symbol", 403)

        # Ensure shares was submitted
        if not sharesToSell:
            return apology("must provide shares", 403)

        # Check if share entered is positive number
        if sharesToSell < 1:
            return apology("invalid number of shares", 403)

        if sharesToSell > sharesInAcc:
            return apology("not enough shares", 403)


        result = lookup(symbol)

        info = {}

        session['price'] = result['price']
        session['transaction'] = 'sold'
        session['cost'] = result['price'] * sharesToSell
        session['symbol'] = symbol
        session['shares'] = sharesToSell
        session['quantity'] = sharesInAcc
        session['cash'] = user[0]['cash']
        session['company'] = result['name']

        info['cost'] = session['cost']
        info['symbol']  = session['symbol']
        info['shares']  = session['shares']
        info['price'] = result['price']
        info['cash'] = user[0]['cash']

        return render_template("sell.html", usd=usd, info=info)

    return render_template("sell.html", userStocks=userStocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
