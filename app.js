const express = require('express');
const url = require('url');
//const triangulate = require('./triangle.js');
const addon = require('./build/Release/addon');
const app = express()
const port = 8080

app.use(express.static('public'));

app.get('/hello', (req, res) => {

  //  const height = req.url.searchParams;
  //  console.log(height);
  const query = url.parse(req.url).query.split('&');
  const height = query.filter(function (el) {
    return el.indexOf('height') !== -1
  })[0].split('=')[1];

  const width = query.filter(function (el) {
    return el.indexOf('width') !== -1
  })[0].split('=')[1];

  const deep = query.filter(function (el) {
    return el.indexOf('deep') !== -1
  })[0].split('=')[1];
  //  console.log(+height, +width, +deep);
  //  const width = req.searchParams.get("width");
  //  const deep = req.searchParams.get("deep");
  //  let par = JSON.parse(req.url.par);
  //  console.log(addon.hello());
  //  triangulate.triangulate();
  //  res.send(addon.add(height, width, deep));

  //  res.set('Content-Type', 'text/plain');
  const ans = addon.triangulate(+height, +width, +deep);
  res.send(ans);
  //  res.write(result);
  //  res.send('Hello World!')
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
