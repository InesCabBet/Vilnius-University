const library = [
  {
    title: "Pinocho",
    author: "Carlo Collodi",
    pages: 120,
    image: "https://wmagazin.com/wp-content/uploads/2024/12/Portadas.2024-mejores-bonitas-pinocho-collodi-WMagazin-e1735465749152.jpg",
    read: false
  },
  {
    title: "Historias de Terror",
    author: "Maria Perez",
    pages: 345,
    image: "https://marketplace.canva.com/EAG0XmGvn1Q/2/0/1003w/canva-portada-para-libro-de-terror-texturizado-rojo-KZUPFETTvAo.jpg",
    read: false
  },
  {
    title: "Sapiens",
    author: "Yuval Noah",
    pages: 210,
    image: "https://thumb.knygos-static.lt/lwR-YGTaLQz-rf0c-csYcHurP9Q=/fit-in/0x801/images/books/1166468/41mjx6yzfel--sx324-bo1-204-203-200-.jpg",
    read: false
  }
];

document.addEventListener("DOMContentLoaded", () => {
  const layout = document.querySelector(".layout");
  layout.addEventListener("click", (event) => {
    if(event.target.classList.contains("delete")){
      const bookCard = event.target.closest(".book");
      if (bookCard){
        bookCard.remove();
      }
    }
  });
});

document.addEventListener("DOMContentLoaded", () => {
  const layout = document.querySelector(".layout");
  layout.addEventListener("click", (event) => {
    if(event.target.classList.contains("book-status")){
      const button = event.target;
      if(button.textContent == "Unread"){
        button.textContent = "Read";
        button.classList.add("read");
      } else {
        button.textContent = "Unread";
        button.classList.remove("read");
      }
    }
  });
});

document.addEventListener("DOMContentLoaded", () => {
  const form = document.querySelector(".book-form");
  const layout = document.querySelector(".layout");
  const newBookButton = document.querySelector(".new-book");
  // Show / hide the form
  newBookButton.addEventListener("click", () => {
    form.style.display = form.style.display === "flex" ? "none" : "flex";
  });
  // Handle form submission
  form.addEventListener("submit", (event) => {
    event.preventDefault(); // stop page reload
    // Get the values
    const title = document.getElementById("title").value;
    const author = document.getElementById("author").value;
    const pages = document.getElementById("pages").value;
    const image = document.getElementById("image").value;
    // Create a new book card
    const bookCard = document.createElement("div");
    bookCard.classList.add("book");
    bookCard.innerHTML = `
      <img src="${image}" alt="${title}"/>
      <p class="book-title">${title}</p>
      <p class="book-author">${author}</p>
      <p class="book-pages">${pages}</p>
      <button class="book-status">Unread</button>
      <button class="delete">Delete</button>
    `;
    // Add it to the layout
    layout.appendChild(bookCard);
    // Reset form
    form.reset();
    form.style.display = "none"; // hide again after submit
  });

  // Make delete buttons work for new books too
  layout.addEventListener("click", (event) => {
    if (event.target.classList.contains("delete")) {
      event.target.closest(".book").remove();
    }
    if (event.target.classList.contains("book-status")) {
      const button = event.target;
      if (button.textContent === "Unread") {
        button.textContent = "Read";
        button.classList.add("read");
      } else {
        button.textContent = "Unread";
        button.classList.remove("read");
      }
    }
  });
});

const cancelButton = document.getElementById("cancel");
cancelButton.addEventListener("click", () => {
  form.reset();              // clear inputs
  form.style.display = "none"; // hide form again
});
