RoboArm Web Bridge

Quick start:

1. Install dependencies

```bash
cd web
npm install
```

2. Start the server (optional: set `SERIAL_PORT` env var to the Arduino serial path)

```bash
SERIAL_PORT=/dev/ttyACM0 npm start
```

On Windows you can pass `SERIAL_PORT` as an environment variable in PowerShell:

```powershell
$env:SERIAL_PORT="COM3"; npm start
```

Open http://localhost:3000 in your browser. The server will send `!WEB_ON` when a client connects and `!WEB_OFF` when disconnecting; commands from the browser are sent as `!<CMD>` to the Arduino (for example `!S`).