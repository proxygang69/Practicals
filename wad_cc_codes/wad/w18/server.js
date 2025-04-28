const express = require('express');
const mongoose = require('mongoose');
const path = require('path');
const app = express();
const port = 3000;

// MongoDB Connection
mongoose.connect('CONNECTION_STRING', {
  useNewUrlParser: true,
  useUnifiedTopology: true
});

// Middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));

// Schema
const songSchema = new mongoose.Schema({
  Song_Name: String,
  Film_Name: String,
  Music_Director: String,
  Singer: String,
  Actor: String,
  Actress: String
});

const Song = mongoose.model('songdetails', songSchema);

// a + b + c: Insert array of 5 songs
app.get('/insert', async (req, res) => {
  await Song.insertMany([
    { Song_Name: 'Kal Ho Na Ho', Film_Name: 'Kal Ho Na Ho', Music_Director: 'Shankar-Ehsaan-Loy', Singer: 'Sonu Nigam', Actor: '', Actress: '' },
    { Song_Name: 'Tum Hi Ho', Film_Name: 'Aashiqui 2', Music_Director: 'Mithoon', Singer: 'Arijit Singh', Actor: '', Actress: '' },
    { Song_Name: 'Zinda', Film_Name: 'Bhaag Milkha Bhaag', Music_Director: 'Shankar-Ehsaan-Loy', Singer: 'Siddharth Mahadevan', Actor: '', Actress: '' },
    { Song_Name: 'Kun Faya Kun', Film_Name: 'Rockstar', Music_Director: 'A. R. Rahman', Singer: 'Mohit Chauhan', Actor: '', Actress: '' },
    { Song_Name: 'Tera Ban Jaunga', Film_Name: 'Kabir Singh', Music_Director: 'Akhil Sachdeva', Singer: 'Akhil Sachdeva', Actor: '', Actress: '' }
  ]);
  res.send("Songs inserted.");
});

// d) Display total count and list all songs
app.get('/songs', async (req, res) => {
  const songs = await Song.find();
  const count = await Song.countDocuments();
  res.send(`
    <h2>Total Songs: ${count}</h2>
    <a href="/">← Back</a>
    <table border="1" cellpadding="10">
      <tr>
        <th>Song Name</th>
        <th>Film Name</th>
        <th>Music Director</th>
        <th>Singer</th>
        <th>Actor</th>
        <th>Actress</th>
      </tr>
      ${songs.map(song => `
        <tr>
          <td>${song.Song_Name}</td>
          <td>${song.Film_Name}</td>
          <td>${song.Music_Director}</td>
          <td>${song.Singer}</td>
          <td>${song.Actor || '-'}</td>
          <td>${song.Actress || '-'}</td>
        </tr>
      `).join('')}
    </table>
  `);
});

// e) List songs by Music Director
app.get('/songs/director/:name', async (req, res) => {
  const songs = await Song.find({ Music_Director: req.params.name });
  res.json(songs);
});

// f) List songs by Music Director + Singer
app.get('/songs/director/:md/singer/:singer', async (req, res) => {
  const songs = await Song.find({
    Music_Director: req.params.md,
    Singer: req.params.singer
  });
  res.json(songs);
});

// g) Delete a song by name
app.get('/delete/:song', async (req, res) => {
  await Song.deleteOne({ Song_Name: req.params.song });
  res.send(`Deleted song "${req.params.song}"`);
});

// h) Add new favorite song
app.get('/add', async (req, res) => {
  const newSong = new Song({
    Song_Name: 'Kesariya',
    Film_Name: 'Brahmastra',
    Music_Director: 'Pritam',
    Singer: 'Arijit Singh',
    Actor: '',
    Actress: ''
  });
  await newSong.save();
  res.send("Favorite song added.");
});

// i) Songs by singer and film
app.get('/songs/singer/:singer/film/:film', async (req, res) => {
  const songs = await Song.find({
    Singer: req.params.singer,
    Film_Name: req.params.film
  });
  res.json(songs);
});

// j) Update song with actor and actress
app.get('/update/:song', async (req, res) => {
  await Song.updateOne({ Song_Name: req.params.song }, {
    $set: { Actor: 'Ranbir Kapoor', Actress: 'Alia Bhatt' }
  });
  res.send(`Updated "${req.params.song}" with Actor and Actress`);
});

// Start server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
