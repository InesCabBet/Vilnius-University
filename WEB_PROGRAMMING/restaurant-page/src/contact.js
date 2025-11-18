export function loadContact() {
  const content = document.getElementById("content");
  content.innerHTML = "";

  const title = document.createElement("h1");
  title.textContent = "Contact Us";

  const info = document.createElement("p");
  info.innerHTML = `
    Email: icb3rg@gmail.com<br>
    Phone: +34 731 371 890 SPAIN<br>
    Address: 13 La Laguna Way, Tenerife<br><br>
    Open daily 9AM – 11PM (or until Ragnarök)
  `;
  info.style.fontSize = "1.4rem";
  info.style.lineHeight = "2";

  content.appendChild(title);
  content.appendChild(info);
}