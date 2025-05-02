// server.js
const express = require('express');
const mongoose = require('mongoose');
const path = require('path');
const app = express();
const port = 3000;

mongoose.connect('mongodb://localhost:27017/', {
  useNewUrlParser: true,
  useUnifiedTopology: true
});

// Middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.json()); // for JSON body
app.use(express.static(path.join(__dirname, 'public')));

// Schema
const studentSchema = new mongoose.Schema({
  Name: String,
  Roll_No: { type: Number, unique: true },
  WAD_Marks: Number,
  CC_Marks: Number,
  DSBDA_Marks: Number,
  CNS_Marks: Number,
  AI_marks: Number
});

const Student = mongoose.model('studentmarks', studentSchema);

// Serve HTML page
app.get('/students', async (req, res) => {
  const students = await Student.find();
  res.json(students);
});


// API to fetch all students (used by frontend via JS)
app.get('/api/students', async (req, res) => {
  const students = await Student.find();
  res.json(students);
});

// API to add a new student
app.post('/api/students', async (req, res) => {
  try {
    const newStudent = new Student(req.body);
    await newStudent.save();
    res.status(201).json({ message: 'Student added successfully' });
  } catch (err) {
    res.status(400).json({ error: 'Failed to add student', details: err });
  }
});

app.post('/add-student', async (req, res) => {
  const { Name, Roll_No, WAD_Marks, CC_Marks, DSBDA_Marks, CNS_Marks, AI_marks } = req.body;

  const newStudent = new Student({
    Name,
    Roll_No,
    WAD_Marks,
    CC_Marks,
    DSBDA_Marks,
    CNS_Marks,
    AI_marks
  });

  try {
    await newStudent.save();
    res.json({ message: 'Student added successfully' });
  } catch (error) {
    console.error('Error adding student:', error);
    res.status(500).json({ message: 'Failed to add student' });
  }
});

// Query students based on specific criteria
app.get('/students-query', async (req, res) => {
  const { subject, condition, marks } = req.query;
  
  // Dynamically create the query based on the user's input
  let query = {};
  const markValue = parseInt(marks, 10);
  
  switch (condition) {
    case 'gt':
      query[subject] = { $gt: markValue }; // Greater than
      break;
    case 'lt':
      query[subject] = { $lt: markValue }; // Less than
      break;
    case 'eq':
      query[subject] = markValue; // Equal to
      break;
    default:
      return res.status(400).send('Invalid condition');
  }

  // Find students matching the query
  const students = await Student.find(query);
  res.json(students);
});


// Other APIs (same as before)
// You can copy/paste your existing /insert, /dsbda-more-20, /update/:name, etc.

// Start server
app.listen(port, () => console.log(`Server running at http://localhost:${port}`));
