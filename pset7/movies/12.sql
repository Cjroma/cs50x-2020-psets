SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE stars.person_id = (SELECT id FROM people WHERE name = 'Johnny Depp') AND
movies.title IN
(SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE stars.person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter'));