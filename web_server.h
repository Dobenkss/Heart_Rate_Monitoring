const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>HEART RATE</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha3/dist/js/bootstrap.bundle.min.js" defer></script>
    <link href="https://fonts.googleapis.com/css2?family=Bebas+Neue&family=Manrope:wght@200..800&display=swap" rel="stylesheet">
    <style>
     body {
            background-color: #121212;
            color: white;
        }

        .navbar {
            background-color: #E0E0E0;
            font-family: 'Bebas Neue';
        }

        .navbar-brand {
            font-weight: bold;
            font-size: 2rem;
        }

        .container {
            margin-top: 50px;
            text-align: center;
            font-family: 'Bebas Neue';
        }

        .btn {
            background-color: #E53935;
            color: white;
            font-family: 'Manrope';
        }

         .btn:hover {
            background-color: #B71C1C;
        }

        .btn:disabled {
            background-color: #9E9E9E;
        }

        .status {
            font-size: 24px;
            margin-top: 20px;
        }

        .status.normal {
            color: green;
        }

        .status.bradycardia {
            color: yellow;
        }

        .status.tachycardia {
            color: red;
        }

        .floating-btn {
            position: fixed;
            bottom: 20px;
            right: 20px;
            background-color: #E53935;
            color: white;
            border-radius: 50%;
            width: 60px;
            height: 60px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 24px;
        }

        .graph-container {
            margin-top: 20px;
            padding: 20px;
            background-color: #1E1E1E;
            border-radius: 10px;
        }

        .divStyle {
        border: 1px solid #DCDCDC;
        border-radius: 10px;
        width: 300px;
        height: 50px;
        margin: 0px auto;
        box-shadow: 0px 2px 3px 0px #DCDCDC;
        position: relative;
      }

      .child {
        width: 300px;
        position: absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
        font-family: 'Manrope';
      }
    </style>
  </head>
  
  <body> 
    <nav class="navbar">
        <div class="container-fluid">
            <a class="navbar-brand" href="#">ur Lub-Dub <img src="image/icon-heart.png" alt="Heart" height="24"></a>
        </div>
    </nav>
  <div class="container">
    <h3 id="user-name" class="mt-4">GRAPH HEART RATE</h3>
    <br>
    <div class="graph-container">
      <p class="text-danger"></p>
      <canvas id="myCanvas" width="300" height="150" style="box-shadow: 0px 2px 3px 0px #DCDCDC;"></canvas>
    <br><br>
    <div class="divStyle">
      <div class="child">
        <img width="27" height="27" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAYAAAA7MK6iAAAABmJLR0QA/wD/AP+gvaeTAAAACXBIWXMAAC4hAAAuIQEHW/z/AAAACXZwQWcAAAAeAAAAHgD4T+E9AAAEI0lEQVRIx52WXWxTZRjHf+9Zt9l1dGMojGlxITLARGRBogkGhpEYjfLhhTo2EtfyockCcoEao4yheGG8MHGJiWOaoKBwY0bQxZg4xobMDJSghsUtsm46JmGjp+1pQdb38YLuC9bT0/2v2vP8n//vfZ/2nPcoEWFM9YbhWuD2voiiClgBFAFh4IKGbyKxcONrWseZRo2GkWfkebcasAlYBniBEeAcwuH+ePhondajY341Bj7oLiwzsjiqYDmp1TOakPXb4mb3FKi7YIkrSx0HFqVqFDg/muCF7fFQzzj4oLuwLCuLDuAe0uvf63Jz5auWNQDwicfju0tldwHzHPReuZng8e3xUI/ap5TLl+ftSrPT29XRHwuvAViQN+sUqFVOGwXOD8TCK1VTXsEWpTiUAfSWtGzVoAxDNWbeyhZX8o+UsUSpejWTRsBQVLkUsgIyj1CKe2fIBeQRA9TsmQfMVKrQACJOrGsPfc769lbue2rdHbUnj33FS73d3P/cs07JUQO4lM41q7SU0uc3Mae8nNING6bUPCUl+J55GndxMSv27UUZhhPwJQM4m861qHrz+OeStWum1OZP+l6wuIwHqiqdgLsMkBY7h1JqPEwSCTw+H96FCycWUlEBwJUznQCUv/UmWTk5tlRBWgwrFvkOGE5lmr9mNR6fj2gwSLD5eHLXFeOLGpvAT7t2c+33P/D4fCzZ6rfjDsdikRajVusbQMqHwKIt1QD0Hvmaf35snTLegsVluIuLiQ8NEbrYzbn6/QAse30P2fn5KXbLp7Va33ABbO77y5V7d5HteHq/PDIxhdWrb+02OebB1jZEhIGW77nS+TNzH3uU6qG/p82JX73qAjAAcubMtuygQ6faiQSDRIJBon195BbNZs7yhyl5Igk+eXLce3bvPtsN5BYVWTDpWGwwjFxPnvdXYKld46qPP6Ks5mV+qX+Xh3bvItvr5VjZg1iDg6TRRSsWLk/+tIzfdLVa3xAhAIzadQ+2tgGw9JUdZHu9mH/2OIGOavCPQaeAAfxW6Awi++0SLre1gQjueXOTC2lNB0VE6gPRUOfka3c8ZvrjkQMgJ1KFXB8eYeTCbxMLSU7ABntiIB55//ard4DrtNajsUi1IN2pogZP3oKJ1lxu70iNRLqtWKSqTmudFgywTWtTJdRG4Np09f4T3zLU3kHvF4f5zzRTcUdUQm2s1To8XVFNfsu8XU2eglWGUj8AbjJTXIusC1jm6VQG26MkYJmnNVIJJDKAJjRSaQdNCwYIRM1mtOwAJJ0XELTsCETN5nRGR4dnTcxsEvROB9SdNTGzyUmmIzCAPxpu0CJvpIQKe/zRcIPTPMdggIBlfiAi70xDfdtvhT7MJCsjMIDfMt8TkboJptTVWOaBTHNsbyc7fZZfWAfgj4bqZ9L/P5FZrj+hbSxaAAAAJXRFWHRjcmVhdGUtZGF0ZQAyMDIzLTA3LTIxVDEzOjM4OjQ3KzA3OjAwEH/56gAAACV0RVh0bW9kaWZ5LWRhdGUAMjAyMy0wNy0yMVQxMzozODo0NyswNzowME/Oj94AAAAASUVORK5CYII="/>
        <label id="" style="font-size:18px;">Heart Rate</label>
        <label id="bpm_Show" style="font-size:36px;"></label>
      </div>
    </div>
    <br>
    </div>
    <button type="button" class="btn mt-4" id="BTN_Start_Stop" onclick="my_BTN_Start_Stop()">Start Calculating HeartBeat</button>
    <p id="show_Info" hidden></p>
    <br>
    <textarea id="log_BPM" name="log_BPM" class="textareaStyle" readonly hidden></textarea>
  </div>
    
    <script src="https://cdn.jsdelivr.net/npm/xlsx/dist/xlsx.full.min.js"></script>
    <script>
      var axis_x = 0;
      var axis_y = 0;
      var last_BPM_TimeStamp = "";
      var count_Down = 3;
      var myInterval_Count_Down;
      
      document.getElementById("bpm_Show").innerHTML = "&nbsp;0 BPM";
      
      var P_show_Info = document.getElementById("show_Info");
      
      setInterval(myTimer, 35);

      if (!!window.EventSource) {
        var source = new EventSource('/events');
        
        source.addEventListener('open', function(e) {
          console.log("Events Connected");
        }, false);
        
        source.addEventListener('error', function(e) {
          if (e.target.readyState != EventSource.OPEN) {
            console.log("Events Disconnected");
          }
        }, false);
        
        source.addEventListener('message', function(e) {
          console.log("message", e.data);
        }, false);

        source.addEventListener('allDataJSON', function(e) {
          console.log("allDataJSON", e.data);
          
          var obj = JSON.parse(e.data);
          var get_Heartbeat_Signal = obj.heartbeat_Signal;
          var get_BPM_TimeStamp = obj.BPM_TimeStamp;
          var get_BPM_Val = obj.BPM_Val;
          var get_BPM_State = obj.BPM_State;

          if (get_Heartbeat_Signal > 850) get_Heartbeat_Signal = 800;
          if (get_Heartbeat_Signal < 350) get_Heartbeat_Signal = 200;
          
          axis_y = map(get_Heartbeat_Signal, 350, 850, 150, 0);
          
          if (get_BPM_State == true) {
            document.getElementById("bpm_Show").innerHTML = "&nbsp;" + get_BPM_Val + " BPM";
            
            if (last_BPM_TimeStamp != get_BPM_TimeStamp) {
              var my_textarea = document.getElementById('log_BPM');
              var lastLog = my_textarea.textContent;
              if (lastLog == "") {
                document.getElementById('log_BPM').textContent =  "Time,BPM\r\n" + get_BPM_TimeStamp + "," + get_BPM_Val;
              }
              else {
                document.getElementById('log_BPM').textContent =  lastLog + "\r\n" + get_BPM_TimeStamp + "," + get_BPM_Val;
              }
              my_textarea.scrollTop = my_textarea.scrollHeight;
            }
            
            last_BPM_TimeStamp = get_BPM_TimeStamp;
          } else {
            document.getElementById("bpm_Show").innerHTML = "&nbsp;0 BPM";
          }
        }, false);
      }

      var canvas = document.getElementById('myCanvas');
      var context = canvas.getContext('2d');
      
      drawGraph();
       
      context.beginPath();
      context.lineWidth = 1;
      context.strokeStyle = '#0583F2';
      
      function drawGraph() {
        context.beginPath();
        context.moveTo(1,150);
        context.lineTo(1,0);
        context.moveTo(50,150);
        context.lineTo(50,0);
        context.moveTo(100,150);
        context.lineTo(100,0);
        context.moveTo(150,150);
        context.lineTo(150,0);
        context.moveTo(200,150);
        context.lineTo(200,0);
        context.moveTo(250,150);
        context.lineTo(250,0);
        context.moveTo(299,150);
        context.lineTo(299,0);

        context.moveTo(0,1);
        context.lineTo(300,1);
        context.moveTo(0,25);
        context.lineTo(300,25);
        context.moveTo(0,50);
        context.lineTo(300,50);
        context.moveTo(0,75);
        context.lineTo(300,75);
        context.moveTo(0,100);
        context.lineTo(300,100);
        context.moveTo(0,125);
        context.lineTo(300,125);
        context.moveTo(0,149);
        context.lineTo(300,149);

        context.lineWidth = 0.5;
        context.strokeStyle = '#DCDCDC';
        context.closePath();
        context.stroke();
      }

      function set_Axis_XY(x,y) {
        context.lineTo(x, y);
        context.stroke();
        if (axis_x > 300) {
           reset_Graph();
        }
      }
     
      function reset_Graph() {
        axis_x = 0; 
        context.clearRect(0,0,300,150);
        context.closePath();
        drawGraph();
        context.beginPath();
        context.lineWidth = 1;
        context.strokeStyle = '#0583F2';
        context.moveTo(0,axis_y);
      }

      function myTimer() {
        axis_x += 3;
        set_Axis_XY(axis_x, axis_y);
      }

      function map( x,  in_min,  in_max,  out_min,  out_max){
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
      }

      // function my_BTN_Start_Stop() {
      //   reset_Graph();
        
      //   var my_BTN_Start_Stop_Text = document.getElementById("BTN_Start_Stop").innerHTML;
      //   if (my_BTN_Start_Stop_Text == "Start Calculating HeartBeat") {
      //     document.getElementById("BTN_Start_Stop").innerHTML = "Stop Calculating HeartBeat";
      //     send_BTN_Cmd("START");
          
      //     count_Down = 3;
      //     P_show_Info.style.display = "block";
      //     document.getElementById("show_Info").innerHTML = "Please Wait...";
      //     myInterval_Count_Down = setInterval(myTimer_Count_Down, 1000);
      //   } else if (my_BTN_Start_Stop_Text == "Stop Calculating HeartBeat") {
      //     document.getElementById("BTN_Start_Stop").innerHTML = "Start Calculating HeartBeat";
      //     send_BTN_Cmd("STOP");
      //   }
      // }
      var bpmValues = [];

      function my_BTN_Start_Stop() {
          reset_Graph();
    
          var my_BTN_Start_Stop_Text = document.getElementById("BTN_Start_Stop").innerHTML;
          if (my_BTN_Start_Stop_Text == "Start Calculating HeartBeat") {
              bpmValues = []; 
              document.getElementById("BTN_Start_Stop").innerHTML = "Stop Calculating HeartBeat";
              send_BTN_Cmd("START");

              setTimeout(() => {
                  document.getElementById("BTN_Start_Stop").innerHTML = "Start Calculating HeartBeat";
                  send_BTN_Cmd("STOP");
            
                  let sum = bpmValues.reduce((a, b) => a + b, 0);
                  let avg = (bpmValues.length > 0) ? (sum / bpmValues.length).toFixed(2) : 0;
                  showAverageBPM(avg);
              }, 60000); 
          } else {
              document.getElementById("BTN_Start_Stop").innerHTML = "Start Calculating HeartBeat";
              send_BTN_Cmd("STOP");
          }
      }

      function showAverageBPM(avg) {
    if (!document.getElementById("bpmModal")) {
        let modal = document.createElement("div");
        modal.id = "bpmModal";
        modal.style.cssText = `
            position: fixed;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            z-index: 1000;
            background-color: #1E1E1E;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
            text-align: center;
        `;

        modal.innerHTML = `
            <h2 style="color: white; font-family: 'Bebas Neue';">Average BPM</h2>
            <p id="bpmValue" style="font-size: 24px; font-weight: bold; font-family: 'Manrope';"></p>
            <div style="margin-top: 20px;">
                <button id="closeModal" style="padding: 10px 20px; background-color: #4CAF50; color: white; border: none; border-radius: 5px; cursor: pointer;">OK</button>
                <button id="saveToCSV" style="padding: 10px 20px; background-color: #2196F3; color: white; border: none; border-radius: 5px; cursor: pointer; margin-right: 10px;">Save</button>
            </div>
          `;

        document.body.appendChild(modal);

        document.getElementById("closeModal").addEventListener("click", () => {
            clear_BPM_Log();
            modal.style.display = "none";
        });

        document.getElementById("saveToCSV").addEventListener("click", () => {
            save_To_CSV(avg);
        });
    }

    let modal = document.getElementById("bpmModal");
    let bpmValue = document.getElementById("bpmValue");

    let status = "";
    let color = "";

    if (avg < 60) {
        status = "Bradikardi";
        color = "#FFC107"; 
    } else if (avg >= 60 && avg <= 100) {
        status = "Normal";
        color = "#4CAF50"; 
    } else {
        status = "Takikardi";
        color = "#F44336"; 
    }

    bpmValue.innerHTML = `${avg} - <span style="color: ${color};">${status}</span>`;
    bpmValue.style.color = color;

    modal.style.display = "block";
}

source.addEventListener('allDataJSON', function(e) {
    var obj = JSON.parse(e.data);
    if (obj.BPM_State == true) {
        bpmValues.push(obj.BPM_Val);
    }
}, false);

      function myTimer_Count_Down() {
        count_Down -= 1;
        document.getElementById("show_Info").innerHTML = "Please Wait " + (count_Down + 1);
        if (count_Down < 0) {
          P_show_Info.style.display = "none";
          myStop_Count_Down();
        }
      }
      
      function myStop_Count_Down() {
        clearInterval(myInterval_Count_Down);
      }
      
function save_To_CSV(avg) {
    let log_BPM = document.getElementById('log_BPM').value || "";
    let csvContent = `${log_BPM}\nAverage BPM,${avg}`;

    let a = document.createElement('a');
    a.href = 'data:text/csv;charset=utf-8,' + encodeURIComponent(csvContent);
    a.download = 'BPMLog.csv';
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
}

function clear_BPM_Log() {
        document.getElementById('log_BPM').textContent = "";
}

      function send_BTN_Cmd(state) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "BTN_Comd?BTN_Start_Get_BPM=" + state, true);
        xhr.send();
      }
    </script>
  </body>
</html>
)=====";