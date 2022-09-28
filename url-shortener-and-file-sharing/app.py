from flask import Flask, render_template, request, redirect, url_for, flash, abort, session, jsonify
import json
import os.path
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.secret_key = 'abc'


@app.route('/')
def home():
    return render_template('home.html', cookies=session.keys())


@app.route('/url-cua-toi', methods=['GET', 'POST'])
def yoururl():
    if request.method == 'POST':
        urls = {}
        if os.path.exists('urls.json'):
            with open('urls.json') as filecheck:
                urls = json.load(filecheck)
        if request.form['url-ra'] in urls.keys():
            flash('Short name already exists')
            return redirect(url_for('home'))

        if 'url-vao' in request.form.keys():
            urls[request.form['url-ra']] = {'url': request.form['url-vao']}
        else:
            f = request.files['file']
            full_name = request.form['url-ra'] + secure_filename(f.filename)
            f.save(
                './static/user_files/' + full_name)
            urls[request.form['url-ra']] = {'file': full_name}

        with open('urls.json', 'w') as url_file:
            json.dump(urls, url_file)
            session[request.form['url-ra']] = True
        return render_template('your_url.html', ketqua=request.form['url-ra'])
    else:
        return redirect(url_for('home'))


@app.route('/<string:ma>')
def return_url(ma):
    if os.path.exists('urls.json'):
        with open('urls.json') as url_file:
            urls = json.load(url_file)
            if ma in urls.keys():
                if 'url' in urls[ma].keys():
                    return redirect(urls[ma]['url'])
                else:
                    return redirect(url_for('static', filename='user_files/' + urls[ma]['file']))
    return abort(404)


@app.errorhandler(404)
def page_khong_tim_thay(error):
    return render_template('page_not_found.html'), 404


@app.route('/api')
def api():
    return jsonify(list(session.keys()))
