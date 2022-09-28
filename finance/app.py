import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)
app.secret_key = 'abc'

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT symbol, share, cash FROM transac WHERE user = ?", session['user_id'])


    return render_template('index.html', stocks = stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get('symbol')
        # if request.form.get('shares')
        if not symbol:
            return apology("cannot leave blank")
        try:
            share = int(request.form.get('shares'))
        except ValueError:
            return apology("not int")
        share = int(request.form.get('shares'))
        if share <= 0:
                return apology("must input valid number")

        info = lookup(symbol)
        if not info:
            return apology("symbol not exist")

        price = info['price']
        total = price * share
        # name = info['name']
        symbol = info['symbol']
        cash = float(db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash'])

        # db.execute("DROP TABLE IF EXISTS transac")
        db.execute("CREATE TABLE IF NOT EXISTS transac (id INTEGER PRIMARY KEY,user TEXT NOT NULL, symbol TEXT NOT NULL, share INTEGER NOT NULL, cash INTEGER NOT NULL)")
        if cash < total:
            return apology("not enough money")
        newcash = cash - total
        db.execute("INSERT INTO transac (user, symbol, share, cash) VALUES (?,?,?,?)", session['user_id'], symbol, share, total)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newcash, session['user_id'])

        return render_template("bought.html", symbol = symbol, cash = newcash, total = total)
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    """Get stock quote."""
    if request.method == "POST":
        quote = request.form.get('symbol')
        info = lookup(quote)
        if not info:
            return apology("incorrect symbol")
        name = info['name']
        symbol = info['symbol']
        price = info['price']
        return render_template("quoted.html", name = name, symbol = symbol, price = price)
    else:
        return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        rows = db.execute("SELECT username FROM users WHERE username = ?", request.form.get('username'))
        # Ensure username was not exists
        # print(rows)
        if rows:
            # get_flashed_message("user already exists")
            return apology("username already exists", 400)
        if request.form.get("username") == '' or request.form.get("password") == '' or request.form.get("confirmation") == '':
            return apology("Cannot leave blank", 400)

        # ensure passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation don't match", 400)
        db.execute("INSERT OR IGNORE INTO users (username, hash) VALUES (?,?)", request.form.get("username"),generate_password_hash(request.form.get("password")))
        # session['user_id'] = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))[0]['id']
        # if not user:
        #     return apology("username already exists")
        # session['user_id'] = user
        return redirect(url_for("index"))
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
