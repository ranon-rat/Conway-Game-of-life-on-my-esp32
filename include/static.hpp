#include <Arduino.h>
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>esp32 server : )</title>
</head>
<style>

    body {
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        font-family: 'Courier New', Courier, monospace;
        background-color: #220014;
        color: #00b93e;
    }

    .cell {
        width: 17px;
        height: 17px;
        border: 1px solid #000;
        border-radius: 3px;
        appearance: none;
        -webkit-appearance: none;
        background-color: #333;  /* Color cuando está muerta */
        cursor: pointer;
    }

    .cell:checked {
        background-color: #00ff00;  /* Color cuando está viva */
    }
    
</style>

<body>
    <h1>
        Conway game in my esp32
    </h1>
    <div id="values">
    </div>
    <footer>
        <a href="https://github.com/ranon-rat">@ranon-rat</a>
    </footer>

    <script>
        const loc = window.location.hostname

        const httpServer = `http://${loc}/map`
        const wsServer = `ws://${loc}/ws`
        const WIDTH = 20
        const HEIGHT = 20
        let update = false
        let initialMap = Array(HEIGHT * WIDTH).fill("-")
        const ws = new WebSocket(wsServer)

        function setupCheckboxes(WIDTH, HEIGHT, initialMap) {
            const valuesElement = document.getElementById("values")
            let rows = ""
            for (let y = 0; y < HEIGHT; y++) {
                let row = "";
                for (let x = 0; x < WIDTH; x++) {
                    row += `<input class="cell" type="checkbox" ${initialMap[y * WIDTH + x] == "#" ? "checked" : ""}>`;
                }
                row += "<br/>";
                rows += row;
            }
            valuesElement.innerHTML = rows
        }
        function updateCells(map) {
            Array.from(document.getElementsByClassName("cell")).map((v, i) => {
                v.checked = map[i] == "#"
            })
        }
        function addEventListeners() {
            Array.from(document.getElementsByClassName("cell")).map((v, i) => {
                v.onchange = (e) => {
                    ws.send(e.target.checked ? `t${i}` : `f${i}`)
                }
            })
        }
        setupCheckboxes(WIDTH, HEIGHT, initialMap);
        addEventListeners();
        console.log(`http://${loc}/map`)
        fetch(`http://${loc}/map`).then(r => r.text()).then(d => updateCells(d))
        ws.onmessage = (e) => {
            if (e.data == "ut") {
                update = true
                return
            }
            if (e.data == "uf") {
                update = false
                return
            }
            updateCells(e.data)
        }
    </script>
</body>
</html>
)rawliteral";