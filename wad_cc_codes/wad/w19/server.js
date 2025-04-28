// server.js
const express = require('express');
const mongoose = require('mongoose');
const path = require('path');
const app = express();
const port = 3000;

mongoose.connect('CONNECTION_STRING', {
  useNewUrlParser: true,
  useUnifiedTopology: true
});

// Middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));

// Schema
const studentSchema = new mongoose.Schema({
  Name: String,
  Roll_No: Number,
  WAD_Marks: Number,
  CC_Marks: Number,
  DSBDA_Marks: Number,
  CNS_Marks: Number,
  AI_marks: Number
});

const Student = mongoose.model('studentmarks', studentSchema);

// Step 2: Insert initial data
app.get('/insert', async (req, res) => {
  await Student.insertMany([
    { Name: 'Alice', Roll_No: 101, WAD_Marks: 25, CC_Marks: 28, DSBDA_Marks: 30, CNS_Marks: 22, AI_marks: 26 },
    { Name: 'Bob', Roll_No: 102, WAD_Marks: 22, CC_Marks: 23, DSBDA_Marks: 18, CNS_Marks: 20, AI_marks: 24 },
    { Name: 'Charlie', Roll_No: 103, WAD_Marks: 30, CC_Marks: 25, DSBDA_Marks: 27, CNS_Marks: 26, AI_marks: 29 },
    { Name: 'David', Roll_No: 104, WAD_Marks: 10, CC_Marks: 15, DSBDA_Marks: 12, CNS_Marks: 13, AI_marks: 17 }
  ]);
  res.send("Data inserted");
});

// Step 3: Display all students
app.get('/students', async (req, res) => {
  const students = await Student.find();
  const count = await Student.countDocuments();
  res.sendFile(path.join(__dirname, 'public', 'students.html'));
});

// Step 4: Students with DSBDA > 20
app.get('/dsbda-more-20', async (req, res) => {
  const students = await Student.find({ DSBDA_Marks: { $gt: 20 } });
  res.json(students);
});

// Step 5: Update student marks by name
app.get('/update/:name', async (req, res) => {
  await Student.updateOne({ Name: req.params.name }, {
    $inc: {
      WAD_Marks: 10,
      CC_Marks: 10,
      DSBDA_Marks: 10,
      CNS_Marks: 10,
      AI_marks: 10
    }
  });
  res.send(`Updated marks for ${req.params.name}`);
});

// Step 6: All subjects > 25
app.get('/all-subjects-25', async (req, res) => {
  const students = await Student.find({
    WAD_Marks: { $gt: 25 },
    CC_Marks: { $gt: 25 },
    DSBDA_Marks: { $gt: 25 },
    CNS_Marks: { $gt: 25 },
    AI_marks: { $gt: 25 }
  });
  res.json(students);
});

// Step 7: WAD and CC < 40
app.get('/math-sci-low', async (req, res) => {
  const students = await Student.find({
    WAD_Marks: { $lt: 40 },
    CC_Marks: { $lt: 40 }
  });
  res.json(students);
});

// Step 8: Delete student
app.get('/delete/:name', async (req, res) => {
  await Student.deleteOne({ Name: req.params.name });
  res.send(`Deleted student ${req.params.name}`);
});

// Server
app.listen(port, () => console.log(`Server running at http://localhost:${port}`));
