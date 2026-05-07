const flashArea = document.getElementById("flash-area");
const ssidInput = document.getElementById("ssid");
const passwordInput = document.getElementById("password");
const tSlider = document.getElementById("t-slider");
const tValue = document.getElementById("t-value");
const startButton = document.getElementById("start-button");
const stopButton = document.getElementById("stop-button");

let T = Number(tSlider.value);
let running = false;
let lastToggle = 0;

// 再生用
let pulses = [];
let pulseIndex = 0;

tSlider.addEventListener("input", () => {
  T = Number(tSlider.value);
  tValue.textContent = T;
});

startButton.addEventListener("click", () => {
  const ssid = ssidInput.value;
  const password = passwordInput.value;

  pulses = buildPulses(ssid, password);
  pulseIndex = 0;

  console.log("SSID:", ssid);
  console.log("PASSWORD:", password);
  console.log("T:", T);
  console.log("pulses:", pulses);

  running = true;
  lastToggle = 0;

  requestAnimationFrame(loop);
});

stopButton.addEventListener("click", () => {
  running = false;
  flashArea.style.backgroundColor = "black";
});

// --------------------
// 送信用データを作る
// --------------------

function buildPulses(ssid, password) {
  const result = [];

  addStart(result);

  addText(result, ssid);

  addPasswordHeader(result);
  addText(result, password);

  addEnd(result);

  return result;
}

function addStart(result) {
  result.push({ color: "green", duration: T * 8 });
  result.push({ color: "black", duration: T * 4 });
  result.push({ color: "green", duration: T * 4 });
  result.push({ color: "black", duration: T * 1 });
}

function addPasswordHeader(result) {
  result.push({ color: "green", duration: T * 4 });
  result.push({ color: "black", duration: T });
}

function addEnd(result) {
  result.push({ color: "green", duration: T * 4 });
  result.push({ color: "black", duration: T * 1 });
}

function addText(result, text) {
  for (let i = 0; i < text.length; i++) {
    const code = text.charCodeAt(i);

    // UTF-8 1バイト文字、つまりASCIIだけ許可
    if (code > 0x7f) {
      alert("UTF-8の1バイト文字のみ対応しています: " + text[i]);
      running = false;
      return;
    }

    addByte(result, code);
  }
}

function addByte(result, code) {
  // 8bitとして送る
  for (let bit = 7; bit >= 0; bit--) {
    const value = (code >> bit) & 1;
    addBit(result, value);
  }
}

function addBit(result, bit) {
  if (bit === 0) {
    addZero(result);
  } else {
    addOne(result);
  }
}

function addZero(result) {
  result.push({ color: "green", duration: T });
  result.push({ color: "black", duration: T });
}

function addOne(result) {
  result.push({ color: "green", duration: T });
  result.push({ color: "black", duration: T*3 });
}

// --------------------
// 点滅列を再生する
// --------------------

function loop(timestamp) {
  if (!running) return;

  if (pulseIndex >= pulses.length) {
    running = false;
    flashArea.style.backgroundColor = "black";
    console.log("送信終了");
    return;
  }

  const pulse = pulses[pulseIndex];

  if (timestamp - lastToggle >= pulse.duration) {
    flashArea.style.backgroundColor = pulse.color;

    lastToggle = timestamp;
    pulseIndex++;
  }

  requestAnimationFrame(loop);
}