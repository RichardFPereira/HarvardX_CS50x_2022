-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Seek for crimes in the date and location given
SELECT description
    FROM crime_scene_reports
        WHERE day = 28 AND month = 7 AND year = 2021 AND street = "Humphrey Street";

--Important information from crime_scene_reports:
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Interviews with witnesses who were present at the crime scene
SELECT name, transcript
    FROM interviews
        WHERE year = 2021 AND month = 7 AND day = 28;
--| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

--| Eugene  | I don't know the thief's name, but it was someone I recognized.
--Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

--| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

--First flight next day from Fiftyville
--DESTINATION: LaGuardia Airport - NEW YORK CITY
SELECT flight.id, flight.origin, airports.city AS destination
    FROM
        (SELECT flights.id, flights.destination_airport_id AS destination, MIN(flights.hour) AS hour, airports.city AS origin
            FROM flights
            JOIN airports ON flights.origin_airport_id = airports.id
                WHERE year = 2021 AND month = 7 AND day = 29) AS flight
    JOIN airports ON flight.destination = airports.id;

--People passport in fligh 36 - Fiftyville to New York
SELECT flight.id, flight.origin, flight.destination, passengers.passport_number
    FROM
        (SELECT flight.id, flight.origin, airports.city AS destination
            FROM
                (SELECT flights.id, flights.destination_airport_id AS destination, MIN(flights.hour) AS hour, airports.city AS origin
                    FROM flights
                    JOIN airports ON flights.origin_airport_id = airports.id
                        WHERE year = 2021 AND month = 7 AND day = 29) AS flight
            JOIN airports ON flight.destination = airports.id) AS flight
    JOIN passengers ON flight.id = passengers.flight_id;

--People info in flight 36
SELECT people.id, people.name, people.phone_number AS phone, people.license_plate AS plate, flight.passport_number AS passport, flight.id, flight.origin, flight.destination
    FROM
        (SELECT flight.id, flight.origin, flight.destination, passengers.passport_number
            FROM
                (SELECT flight.id, flight.origin, airports.city AS destination
                    FROM
                        (SELECT flights.id, flights.destination_airport_id AS destination, MIN(flights.hour) AS hour, airports.city AS origin
                            FROM flights
                            JOIN airports ON flights.origin_airport_id = airports.id
                                WHERE year = 2021 AND month = 7 AND day = 29) AS flight
                    JOIN airports ON flight.destination = airports.id) AS flight
            JOIN passengers ON flight.id = passengers.flight_id) AS flight
    JOIN people ON flight.passport_number = people.passport_number;

--People account add to the table
SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, bank_accounts.account_number AS account, suspect.id AS flight_id, suspect.origin, suspect.destination
    FROM
        (SELECT people.id, people.name, people.phone_number AS phone, people.license_plate AS plate, flight.passport_number AS passport, flight.id, flight.origin, flight.destination
            FROM
                (SELECT flight.id, flight.origin, flight.destination, passengers.passport_number
                    FROM
                        (SELECT flight.id, flight.origin, airports.city AS destination
                            FROM
                                (SELECT flights.id, flights.destination_airport_id AS destination, MIN(flights.hour) AS hour, airports.city AS origin
                                    FROM flights
                                    JOIN airports ON flights.origin_airport_id = airports.id
                                        WHERE year = 2021 AND month = 7 AND day = 29) AS flight
                            JOIN airports ON flight.destination = airports.id) AS flight
                    JOIN passengers ON flight.id = passengers.flight_id) AS flight
            JOIN people ON flight.passport_number = people.passport_number) AS suspect
    JOIN bank_accounts ON suspect.id = bank_accounts.person_id;

--People who used the ATM in day 28 month 7 year 2021 in Leggett Street and the operation type was a withdraw
SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, suspect.account, suspect.flight_id, suspect.origin, suspect.destination
    FROM
        (SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, bank_accounts.account_number AS account, suspect.id AS flight_id, suspect.origin, suspect.destination
            FROM
                (SELECT people.id, people.name, people.phone_number AS phone, people.license_plate AS plate, flight.passport_number AS passport, flight.id, flight.origin, flight.destination
                    FROM
                        (SELECT flight.id, flight.origin, flight.destination, passengers.passport_number
                            FROM
                                (SELECT flight.id, flight.origin, airports.city AS destination
                                    FROM
                                        (SELECT flights.id, flights.destination_airport_id AS destination, MIN(flights.hour) AS hour, airports.city AS origin
                                            FROM flights
                                            JOIN airports ON flights.origin_airport_id = airports.id
                                                WHERE year = 2021 AND month = 7 AND day = 29) AS flight
                                    JOIN airports ON flight.destination = airports.id) AS flight
                            JOIN passengers ON flight.id = passengers.flight_id) AS flight
                    JOIN people ON flight.passport_number = people.passport_number) AS suspect
            JOIN bank_accounts ON suspect.id = bank_accounts.person_id) as suspect
    JOIN atm_transactions ON suspect.account = atm_transactions.account_number
        WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

--People who was leaving in baker in the crime day in a interval time of ten minutes after the theft
SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, suspect.account, suspect.flight_id, suspect.origin, suspect.destination
    FROM
        (SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, suspect.account, suspect.flight_id, suspect.origin, suspect.destination
            FROM
                (SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, bank_accounts.account_number AS account, suspect.id AS flight_id, suspect.origin, suspect.destination
                    FROM
                        (SELECT people.id, people.name, people.phone_number AS phone, people.license_plate AS plate, flight.passport_number AS passport, flight.id, flight.origin, flight.destination
                            FROM
                                (SELECT flight.id, flight.origin, flight.destination, passengers.passport_number
                                    FROM
                                        (SELECT flight.id, flight.origin, airports.city AS destination
                                            FROM
                                                (SELECT flights.id, flights.destination_airport_id AS destination, MIN(flights.hour) AS hour, airports.city AS origin
                                                    FROM flights
                                                    JOIN airports ON flights.origin_airport_id = airports.id
                                                        WHERE year = 2021 AND month = 7 AND day = 29) AS flight
                                            JOIN airports ON flight.destination = airports.id) AS flight
                                    JOIN passengers ON flight.id = passengers.flight_id) AS flight
                            JOIN people ON flight.passport_number = people.passport_number) AS suspect
                    JOIN bank_accounts ON suspect.id = bank_accounts.person_id) as suspect
            JOIN atm_transactions ON suspect.account = atm_transactions.account_number
                WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AS suspect
    JOIN bakery_security_logs ON suspect.plate = bakery_security_logs.license_plate
        WHERE activity = "exit" AND hour = 10 AND minute <= 25;

--People who called someone that day with duration less than 1 minute and the phone number of the receiver
SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, suspect.account, suspect.flight_id, suspect.origin, suspect.destination, phone_calls.receiver
    FROM
        (SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, suspect.account, suspect.flight_id, suspect.origin, suspect.destination
    FROM
        (SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, suspect.account, suspect.flight_id, suspect.origin, suspect.destination
            FROM
                (SELECT suspect.id, suspect.name, suspect.phone, suspect.plate, suspect.passport, bank_accounts.account_number AS account, suspect.id AS flight_id, suspect.origin, suspect.destination
                    FROM
                        (SELECT people.id, people.name, people.phone_number AS phone, people.license_plate AS plate, flight.passport_number AS passport, flight.id, flight.origin, flight.destination
                            FROM
                                (SELECT flight.id, flight.origin, flight.destination, passengers.passport_number
                                    FROM
                                        (SELECT flight.id, flight.origin, airports.city AS destination
                                            FROM
                                                (SELECT flights.id, flights.destination_airport_id AS destination, MIN(flights.hour) AS hour, airports.city AS origin
                                                    FROM flights
                                                    JOIN airports ON flights.origin_airport_id = airports.id
                                                        WHERE year = 2021 AND month = 7 AND day = 29) AS flight
                                            JOIN airports ON flight.destination = airports.id) AS flight
                                    JOIN passengers ON flight.id = passengers.flight_id) AS flight
                            JOIN people ON flight.passport_number = people.passport_number) AS suspect
                    JOIN bank_accounts ON suspect.id = bank_accounts.person_id) as suspect
            JOIN atm_transactions ON suspect.account = atm_transactions.account_number
                WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AS suspect
    JOIN bakery_security_logs ON suspect.plate = bakery_security_logs.license_plate
        WHERE activity = "exit" AND hour = 10 AND minute <= 25) as suspect
    JOIN phone_calls ON suspect.phone = phone_calls.caller
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60;

--*** BRUCE IS THE THIEF, HE SCAPED TO NEW YORK CITY AND CALLED "(375) 555-8161" ***

--***THE PERSON WHO HELPED BRUCE TO SCAPE
SELECT *
    FROM people
        WHERE phone_number = "(375) 555-8161";