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
let wait = 0;         // 今出している色を出し続ける時間 [ms]

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
  if (!pulses) return;   // ASCII 以外の文字があったので送らない
  pulseIndex = 0;

  // SSID とパスワードは開発者ツールに残さない
  console.log("T:", T, "ms / pulses:", pulses.length);

  running = true;
  lastToggle = 0;
  wait = 0;

  requestAnimationFrame(loop);
});

stopButton.addEventListener("click", () => {
  running = false;
  flashArea.style.backgroundColor = "black";
});

// --------------------
// 送信用データを作る
// --------------------

// 送る順番: 開始 → SSID → 区切り → パスワード → 区切り → チェックサム(1 バイト) → 終わり
// ASCII 以外の文字があれば null を返す
function buildPulses(ssid, password) {
  const result = [];

  addStart(result);

  if (!addText(result, ssid)) return null;

  addPasswordHeader(result);
  if (!addText(result, password)) return null;

  // チェックサム: SSID とパスワードの全バイトの合計の下位 8 ビット。受け取り側で読み違いに気づける
  addPasswordHeader(result);   // 区切りは同じ形(緑 4T、黒 1T)
  addByte(result, checksum(ssid + password));

  addEnd(result);

  return result;
}

function checksum(text) {
  let sum = 0;
  for (let i = 0; i < text.length; i++) sum = (sum + text.charCodeAt(i)) & 0xff;
  return sum;
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

// 送れたら true、ASCII 以外の文字があれば false
function addText(result, text) {
  for (let i = 0; i < text.length; i++) {
    const code = text.charCodeAt(i);

    // UTF-8 1バイト文字、つまりASCIIだけ許可
    if (code > 0x7f) {
      alert("UTF-8の1バイト文字のみ対応しています: " + text[i]);
      return false;
    }

    addByte(result, code);
  }
  return true;
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

  // 今の色を wait [ms] 出し終えたら次の色に切り替える
  if (timestamp - lastToggle >= wait) {
    flashArea.style.backgroundColor = pulse.color;
    wait = pulse.duration;

    lastToggle = timestamp;
    pulseIndex++;
  }

  requestAnimationFrame(loop);
}