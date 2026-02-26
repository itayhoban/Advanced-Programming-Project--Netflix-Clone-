const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const mongoose = require('mongoose');
const users = require('./routes/user'); // Import routes for users
const category = require('./routes/category');
const movie = require('./routes/movie');
const token = require('./routes/token');
require('custom-env').env(process.env.NODE_ENV, './config');
mongoose.connect(process.env.CONNECTION_STRING);

var app = express();
app.use(cors());
app.use(bodyParser.urlencoded({extended : true}));
app.use(express.json());
app.use('/users', users);
app.use('/categories', category);
app.use('/movies', movie);
app.use('/tokens', token);
app.listen(process.env.PORT);