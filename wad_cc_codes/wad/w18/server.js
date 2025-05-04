// server.js
const express = require('express');
const mongoose = require('mongoose');
const path = require('path');
const app = express();
const port = 3000;

// MongoDB Connection
mongoose.connect('mongodb://localhost:27017/', {
  useNewUrlParser: true,
  useUnifiedTopology: true
});

// Middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));

// Schema
const songSchema = new mongoose.Schema({
  Song_Name: { type: String, unique: true },
  Film_Name: String,
  Music_Director: String,
  Singer: String,
  Actor: String,
  Actress: String,
  Favorite: { type: Boolean, default: false }
});

const Song = mongoose.model('songdetails', songSchema);

// Automatically insert predefined songs if they don't exist
app.get('/init', async (req, res) => {
  const defaultSongs = [
    { Song_Name: 'Kal Ho Na Ho', Film_Name: 'Kal Ho Na Ho', Music_Director: 'Shankar-Ehsaan-Loy', Singer: 'Sonu Nigam' },
    { Song_Name: 'Tum Hi Ho', Film_Name: 'Aashiqui 2', Music_Director: 'Mithoon', Singer: 'Arijit Singh' },
    { Song_Name: 'Zinda', Film_Name: 'Bhaag Milkha Bhaag', Music_Director: 'Shankar-Ehsaan-Loy', Singer: 'Siddharth Mahadevan' },
    { Song_Name: 'Kun Faya Kun', Film_Name: 'Rockstar', Music_Director: 'A. R. Rahman', Singer: 'Mohit Chauhan' },
    { Song_Name: 'Tera Ban Jaunga', Film_Name: 'Kabir Singh', Music_Director: 'Akhil Sachdeva', Singer: 'Akhil Sachdeva' }
  ];

  let inserted = 0;
  for (const song of defaultSongs) {
    const exists = await Song.exists({ Song_Name: song.Song_Name });
    if (!exists) {
      await Song.create(song);
      inserted++;
    }
  }

  res.send(inserted ? `Inserted ${inserted} default songs.` : "Default songs already present.");
});

// JSON route to return song list
app.get('/songs', async (req, res) => {
  const songs = await Song.find();
  const count = await Song.countDocuments();
  res.json({ count, songs });
});

// Delete a song by name
app.get('/delete/:song', async (req, res) => {
  await Song.deleteOne({ Song_Name: req.params.song });
  res.send(`Deleted song "${req.params.song}"`);
});

// Add a song
app.get('/add', async (req, res) => {
  const { Song_Name, Film_Name, Music_Director, Singer, Actor = '', Actress = '' } = req.query;

  if (!Song_Name || !Film_Name || !Music_Director || !Singer) {
    return res.status(400).send("Missing required fields: Song_Name, Film_Name, Music_Director, Singer");
  }

  const exists = await Song.exists({ Song_Name });

  if (exists) {
    return res.send(`${Song_Name} already exists in the database.`);
  }

  const newSong = new Song({
    Song_Name,
    Film_Name,
    Music_Director,
    Singer,
    Actor,
    Actress
  });

  await newSong.save();
  res.send(`${Song_Name} added successfully.`);
});

// Toggle favorite
app.put('/favorite/:name', async (req, res) => {
  try {
    const song = await Song.findOne({ Song_Name: req.params.name });
    if (!song) return res.send("Song not found");

    song.Favorite = !song.Favorite;
    await song.save();
    res.send(`Marked as ${song.Favorite ? "Favorite ★" : "Not Favorite ☆"}`);
  } catch (err) {
    console.error(err);
    res.status(500).send("Error updating favorite");
  }
});

// Start server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
