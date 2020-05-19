SELECT name FROM people
WHERE name != 'Kevin Bacon' AND id IN (SELECT person_id FROM stars
WHERE movie_id IN
(SELECT id FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE person_id = (SELECT id FROM people
WHERE name = 'Kevin Bacon' AND birth = 1958)));