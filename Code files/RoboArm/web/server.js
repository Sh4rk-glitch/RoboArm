const express = require('express');
const { WebSocketServer } = require('ws');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const app = express();
const port = process.env.PORT || 3000;

app.use(express.static('public'));

const server = app.listen(port, () => {
  console.log(`Web UI available at http://localhost:${port}`);
});

const wss = new WebSocketServer({ server });

// Choose serial port: either env var SERIAL_PORT or attempt to auto-detect
async function choosePort() {
  if (process.env.SERIAL_PORT) return process.env.SERIAL_PORT;
  const ports = await SerialPort.list();
  if (ports.length === 0) throw new Error('No serial ports found');
  // prefer Arduino-like
  const arduino = ports.find(p => (p.manufacturer || '').toLowerCase().includes('arduino'));
  return (arduino && arduino.path) ? arduino.path : ports[0].path;
}

let sp; let parser;

choosePort().then(path => {
  console.log('Opening serial port', path);
  sp = new SerialPort({ path, baudRate: 4800 });
  parser = sp.pipe(new ReadlineParser({ delimiter: '\r\n' }));

  parser.on('data', line => {
    console.log('<-', line);
    // broadcast to all websocket clients
    wss.clients.forEach(ws => {
      if (ws.readyState === ws.OPEN) ws.send(line);
    });
  });

  sp.on('error', err => console.error('Serial error', err.message));
}).catch(err => {
  console.error('Serial port open failed:', err.message);
});

wss.on('connection', ws => {
  console.log('Client connected');
  // tell Arduino web control is active
  if (sp && sp.isOpen) sp.write('!WEB_ON\n');

  ws.on('message', msg => {
    // expect simple command like 'S' or longer sequences; prefix with '!' so Arduino treats as web command
    const text = msg.toString();
    if (sp && sp.isOpen) {
      sp.write('!' + text + '\n');
    }
  });

  ws.on('close', () => {
    console.log('Client disconnected');
    // turn off web mode when no clients connected
    setTimeout(() => {
      const anyOpen = Array.from(wss.clients).some(c => c.readyState === c.OPEN);
      if (!anyOpen && sp && sp.isOpen) sp.write('!WEB_OFF\n');
    }, 200);
  });
});

process.on('SIGINT', () => process.exit());
