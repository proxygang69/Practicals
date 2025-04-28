document.addEventListener("DOMContentLoaded", () => {
    const form = document.getElementById("registrationForm");
    const resetBtn = document.getElementById("resetBtn");
    const userList = document.getElementById("userList");
  
    form.addEventListener("submit", function (event) {
      event.preventDefault();
  
      const name = document.getElementById("name").value;
      const email = document.getElementById("email").value;
      const username = document.getElementById("username").value;
  
      const userData = { name, email, username };
  
      fetch("https://jsonplaceholder.typicode.com/users", {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify(userData)
      })
        .then(response => response.json())
        .then(data => {
          displayUser(data);
          form.reset();
        })
        .catch(error => console.error("Error:", error));
    });
  
    resetBtn.addEventListener("click", () => {
      form.reset();
    });
  
    function displayUser(user) {
      const card = document.createElement("div");
      card.className = "user-card";
      card.innerHTML = `
        <strong>Name:</strong> ${user.name}<br>
        <strong>Email:</strong> ${user.email}<br>
        <strong>Username:</strong> ${user.username}
      `;
      userList.appendChild(card);
    }
  });
  