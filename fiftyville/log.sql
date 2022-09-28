-- Keep a log of any SQL queries you execute as you solve the mystery.

-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bakery_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

--check the crime scene
SELECT description FROM crime_scene_reports
    WHERE month = 7 AND day = 28 and street = 'Humphrey Street';
-- | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | Littering took place at 16:36. No known witnesses.

SELECT * FROM interviews
    WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

SELECT license_plate AS suspect_license FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25;
-- +-----------------+
-- | suspect_license |
-- +-----------------+
-- | 5P2BI95         |
-- | 94KL13X         |
-- | 6P58WS2         |
-- | 4328GD8         |
-- | G412CB7         |
-- | L93JTIZ         |
-- | 322W7JE         |
-- | 0NTHK55         |
-- +-----------------+

SELECT account_number AS suspect_account FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';
-- +-----------------+
-- | suspect_account |
-- +-----------------+
-- | 28500762        |
-- | 28296815        |
-- | 76054385        |
-- | 49610011        |
-- | 16153065        |
-- | 25506511        |
-- | 81061156        |
-- | 26013199        |
-- +-----------------+

SELECT person_id FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number AS suspect_account FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw');
-- +-----------+
-- | person_id |
-- +-----------+
-- | 686048    |
-- | 514354    |
-- | 458378    |
-- | 395717    |
-- | 396669    |
-- | 467400    |
-- | 449774    |
-- | 438727    |
-- +-----------+

SELECT id, caller, receiver, duration
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- +-----+----------------+----------------+----------+
-- | id  |     caller     |    receiver    | duration |
-- +-----+----------------+----------------+----------+
-- | 221 | (130) 555-0289 | (996) 555-8899 | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 45       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 54       |
-- +-----+----------------+----------------+----------+

SELECT * FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29
    AND origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE '%Fiftyville%') ORDER BY hour LIMIT 1;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

SELECT passport_number AS suspect_passport FROM passengers
    WHERE flight_id
    IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE '%Fiftyville%') ORDER BY hour LIMIT 1);
-- +------------------+
-- | suspect_passport |
-- +------------------+
-- | 7214083635       |
-- | 1695452385       |
-- | 5773159633       |
-- | 1540955065       |
-- | 8294398571       |
-- | 1988161715       |
-- | 9878712108       |
-- | 8496433585       |
-- +------------------+
SELECT caller AS suspect_caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

SELECT name FROM people
    WHERE passport_number IN
        (SELECT passport_number FROM passengers
        WHERE flight_id
        IN (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE '%Fiftyville%') ORDER BY hour LIMIT 1))
    AND phone_number IN
        (SELECT caller
        FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
    AND license_plate IN
        (SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25)
    AND id IN
        (SELECT person_id FROM bank_accounts
        WHERE account_number IN
        (SELECT account_number AS suspect_account FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'));
-- Suspect is:
-- +-------+
-- | name  |
-- +-------+
-- | Bruce |
-- +-------+

SELECT city FROM airports WHERE id =
    (SELECT destination_airport_id FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29
    AND origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE '%Fiftyville%') ORDER BY hour LIMIT 1);
-- Suspect destination:
-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+
SELECT name FROM people
    WHERE phone_number IN (SELECT receiver FROM phone_calls
    WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce')
    AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);
-- ACCOMPLICE:
-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+

