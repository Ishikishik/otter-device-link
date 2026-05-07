const flashArea = document.getElementById("flash-area");
const ssidInput = document.getElementById("ssid");
const passwordInput = document.getElementById("password");
const tSlider = document.getElementById("t-slider");
const tValue = document.getElementById("t-value");
const startButton = document.getElementById("start-button");
const stopButton = document.getElementById("stop-button");

let T = Number(tSlider.value);
let running = false;
let isWhite = false;
let lastToggle = 0;

tSlider.addEventListener("input", () => {
  T = Number(tSlider.value);
  tValue.textContent = T;
});

startButton.addEventListener("click", () => {
  const ssid = ssidInput.value;
  const password = passwordInput.value;

  console.log("SSID:", ssid);
  console.log("PASSWORD:", password);
  console.log("T:", T);

  running = true;
  lastToggle = 0;
  requestAnimationFrame(loop);
});

stopButton.addEventListener("click", () => {
  running = false;
  flashArea.style.backgroundColor = "black";
});

function loop(timestamp) {
  if (!running) return;

  if (timestamp - lastToggle >= T) {
    isWhite = !isWhite;
    flashArea.style.backgroundColor = isWhite ? "white" : "black";
    lastToggle = timestamp;
  }

  requestAnimationFrame(loop);
}