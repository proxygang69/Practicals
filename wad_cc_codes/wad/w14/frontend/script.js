fetch('http://localhost:3000/api/users')
  .then(response => response.json())
  .then(users => {
    const list = document.getElementById('userList');
    users.forEach(user => {
      const card = document.createElement('div');
      card.className = 'user-card';
      card.innerHTML = `
        <h2>${user.name}</h2>
        <p>${user.email}</p>
      `;
      list.appendChild(card);
    });
  })
  .catch(error => console.error('Error fetching users:', error));
