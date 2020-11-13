import 'regenerator-runtime/runtime'
import Tweezer from 'tweezer.js'

document.addEventListener('DOMContentLoaded', (event) => {
  setInterval(async () => {
    let val = await postReq('/');
    val = Math.floor(val);
    countTo(val);
  }, 5000);
});

function countTo(val) {
  const obj = document.getElementById('percentage');
  const current = parseInt(document.getElementById('percentage').innerHTML, 10);
  new Tweezer({
    start: current,
    end: val,
    duration: 3000,
    easing: (t, b, c, d) => {
      if ((t /= d / 2) < 1) return c / 2 * t * t + b
      return -c / 2 * ((--t) * (t - 2) - 1) + b
    }
  })
    .on('tick', v => obj.innerHTML = v)
    .begin()
}

async function postReq(url) {
  const response = await fetch(url, {
    method: 'POST',
    credentials: 'same-origin',
  });
  return response.json(); 
}