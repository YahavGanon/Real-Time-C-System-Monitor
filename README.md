# Real-Time OS Resource Monitor (C & JavaScript)

I developed this project to explore Socket Programming in C and bridge the gap between low-level system data and modern web-based visualization. 

The application retrieves real-time physical RAM usage from the Windows OS and streams it directly to a dynamic dashboard in the browser.

## 📊 Live Demo
![Project Demo](Animation.gif)

## How It Works

### The Backend (C)
* **Socket Programming:** Built a TCP server using **Winsock** that listens on port 8080.
* **Windows API:** Utilized the `GlobalMemoryStatusEx` function from the **Win32 API** to fetch live hardware telemetry.
* **JSON Response:** The server formats the hardware data into a JSON string to ensure seamless parsing by the frontend.

### The Frontend (HTML/JS)
* **Fetch API:** Implemented a request loop that polls the C server every 1000ms for updated memory stats.
* **Chart.js:** Integrated this library to visualize raw data into a responsive, real-time line graph.

## Challenges & Learning
* **CORS Policy:** Encountered and solved Cross-Origin Resource Sharing issues by implementing custom HTTP headers in the C backend.
* **Socket Lifecycle:** Managed the connection sequence to ensure the server doesn't abort the socket before the data transmission is fully acknowledged by the browser.

## How to Run
1. **Compile:** Open `server.c` in Visual Studio and compile (ensure `ws2_32.lib` is linked).
2. **Execute:** Run the generated `.exe` file.
3. **Visualize:** Open `index.html` in any modern web browser.
