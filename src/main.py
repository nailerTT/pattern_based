from pbd import app
from pbd.database import database
import sys
import os

if len(sys.argv) == 1:
    dataset_str = "default"
    db = database.database()

app.config['DATASET'] = dataset_str
app.config['DATABASE'] = db
app.config['TEMPLATES_AUTO_RELOAD']=True
app.config['DEBUG'] = True

if "DEBUG" in os.environ:
    app.config['DEBUG'] = True

if "TESTING" in os.environ:
    app.config['TESTING'] = True

app.run(host='0.0.0.0', port=9090)
