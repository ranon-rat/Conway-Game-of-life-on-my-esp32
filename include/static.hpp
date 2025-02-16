#include <Arduino.h>
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>esp32 server : )</title>
</head>

<body>
    <h1>
        Conway game in my esp32
    </h1>
    <div id="values">
    </div>
    <footer>
        @ranon-rat
    </footer>
    <script>
     

        const WIDTH = 20
        const HEIGHT = 20
        let initialMap = Array(HEIGHT * WIDTH).fill("-")
        function setupCheckboxes(WIDTH, HEIGHT, initialMap) {
            const valuesElement = document.getElementById("values")
            let rows = ""
            for (let y = 0; y < HEIGHT; y++) {
                let row = "<p>";
                for (let x = 0; x < WIDTH; x++) {
                    row += `<input class="cell" type="checkbox" ${initialMap[y * WIDTH + x] == "#" ? "checked" : ""}>`;
                }
                row += "</p>";
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
                    console.log(e, i)
                }
            })
        }
        setupCheckboxes(WIDTH, HEIGHT, initialMap);
        addEventListeners();
        updateCells("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------###------------------------------------------------------------------")
        
    </script>
</body>

</html>

)rawliteral";