export function loadMenu() {
  const content = document.getElementById("content");
  content.innerHTML = "";

  const title = document.createElement("h1");
  title.textContent = "Our Menu";
  const list = document.createElement("ul");
  list.style.listStyle = "none";
  list.style.padding = "2rem";
  list.style.fontSize = "1.4rem";

  const items = [
    "Mjolnir Steak - $99",
    "Valhalla Salad - $25",
    "Asgardian Mead - $15",
    "Yggdrasil Soup - $18",
    "Fenrir Burger - $35",
  ];

  items.forEach((item) => {
    const li = document.createElement("li");
    li.textContent = item;
    li.style.margin = "1rem 0";
    li.style.padding = "1rem";
    li.style.background = "#fff";
    li.style.borderRadius = "8px";
    li.style.boxShadow = "0 2px 5px rgba(0,0,0,0.1)";
    list.appendChild(li);
  });

  content.appendChild(title);
  content.appendChild(list);
}