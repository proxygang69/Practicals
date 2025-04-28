const express = require('express');
const router = express.Router();
const Book = require('../models/Book');

// ➡ Add New Book
router.post('/', async (req, res) => {
  try {
    const { title, author, price, genre } = req.body;
    const newBook = new Book({ title, author, price, genre });
    await newBook.save();
    res.status(201).json(newBook);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
});

// ➡ Get All Books
router.get('/', async (req, res) => {
  try {
    const books = await Book.find();
    res.json(books);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

// ➡ Update Book
router.put('/:id', async (req, res) => {
  try {
    const { title, author, price, genre } = req.body;
    const updatedBook = await Book.findByIdAndUpdate(
      req.params.id,
      { title, author, price, genre },
      { new: true }
    );
    res.json(updatedBook);
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
});

// ➡ Delete Book
router.delete('/:id', async (req, res) => {
  try {
    await Book.findByIdAndDelete(req.params.id);
    res.json({ message: 'Book deleted successfully' });
  } catch (err) {
    res.status(400).json({ message: err.message });
  }
});

module.exports = router;
