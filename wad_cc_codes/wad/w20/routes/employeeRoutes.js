const express = require('express');
const Employee = require('../models/Employee');
const router = express.Router();

// Add a new employee
router.post('/employees', async (req, res) => {
  try {
    const { name, department, designation, salary, joiningDate } = req.body;
    const newEmployee = new Employee({ name, department, designation, salary, joiningDate });
    await newEmployee.save();
    res.status(201).json(newEmployee);
  } catch (err) {
    res.status(400).json({ error: 'Error adding employee' });
  }
});

// Get all employee records
router.get('/employees', async (req, res) => {
  try {
    const employees = await Employee.find();
    res.status(200).json(employees);
  } catch (err) {
    res.status(400).json({ error: 'Error fetching employees' });
  }
});

// Update an existing employee's details
router.put('/employees/:id', async (req, res) => {
  try {
    const { name, department, designation, salary, joiningDate } = req.body;
    const updatedEmployee = await Employee.findByIdAndUpdate(
      req.params.id,
      { name, department, designation, salary, joiningDate },
      { new: true }
    );
    res.status(200).json(updatedEmployee);
  } catch (err) {
    res.status(400).json({ error: 'Error updating employee' });
  }
});

// Delete an employee record
router.delete('/employees/:id', async (req, res) => {
  try {
    await Employee.findByIdAndDelete(req.params.id);
    res.status(200).json({ message: 'Employee deleted successfully' });
  } catch (err) {
    res.status(400).json({ error: 'Error deleting employee' });
  }
});

module.exports = router;
