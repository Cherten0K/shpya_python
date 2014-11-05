# -*- coding: utf-8 -*-
import os
import sys
from sqlite3 import dbapi2 as sqlite3
from flask import Flask, request, session, g, redirect, url_for, \
    render_template, flash


app = Flask(__name__)

app.config.update(dict(
    DATABASE=os.path.join(app.root_path, 'base.db'),
    DEBUG=True,
    SECRET_KEY='development key'
))
app.config.from_envvar('LINKS_SETTINGS', silent=True)


def connect_db():
    """Connects to the specific database."""
    rv = sqlite3.connect(app.config['DATABASE'])
    rv.row_factory = sqlite3.Row
    return rv


def init_db():
    """Creates the database tables."""
    with app.app_context():
        db = get_db()
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()


def get_db():
    """Opens a new database connection if there is none yet for the
    current application context.
    """
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connect_db()
    return g.sqlite_db


@app.teardown_appcontext
def close_db(error):
    """Closes the database again at the end of the request."""
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()


@app.route('/')
def main_page():
    if not ('logged_in' in session):
        return render_template('main.html')
    db = get_db()
    cur = db.execute('SELECT title, comment, start_date, end_date FROM entries where user=?', [session['login']])
    entries = cur.fetchall()
    entries.reverse()
    return render_template('main.html', messages=entries)


@app.route('/append', methods=['POST'])
def append():
    db = get_db()
    cur = db.cursor()
    cur.execute('INSERT INTO entries (user, title, comment, start_date, end_date) VALUES (?, ?, ?, ? ,?)',
                [session['login'], request.form['title'], request.form['comment'],
                 request.form['start_date'], request.form['end_date']])
    db.commit()
    return redirect(url_for('main_page'))


@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        db = get_db()
        cur = db.execute('SELECT count(*) FROM users where login=? and password=?',
                         [request.form['login'], request.form['password']])
        result=cur.fetchone()
        if result[0] != 1:
            error = 'Invalid username or password'
        else:
            session['logged_in'] = True
            session['login'] = request.form['login']
            flash('You were logged in')
            return redirect(url_for('main_page'))
    return render_template('login.html', error=error)


@app.route('/register', methods=['GET', 'POST'])
def register():
    error = None
    if request.method == 'POST':
        db = get_db()
        cur = db.execute('SELECT count(*) FROM users where login=?',
                         [request.form['login']])
        result=cur.fetchone()
        if result[0] == 1:
            error = 'User exists'
        else:
            cur = db.cursor()
            cur.execute('INSERT INTO users (login, password) VALUES (?, ?)',
                [request.form['login'], request.form['password']])
            db.commit()
            session['logged_in'] = True
            session['login'] = request.form['login']
            flash('You were signed up and logged in')
            return redirect(url_for('main_page'))
    return render_template('register.html', error=error)


@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('login', None)
    flash('You were logged out')
    return redirect(url_for('main_page'))


def main():
    if len(sys.argv) > 1:
        init_db()
    app.run()


if __name__ == '__main__':
    main()
