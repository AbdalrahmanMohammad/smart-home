// checkConnection.js

function Check_Connection(id) {
    // Create a div element for the sticky red rectangle
    const connectionStatusDiv = document.createElement('div');
    connectionStatusDiv.style.position = 'fixed';
    connectionStatusDiv.style.top = '0';
    connectionStatusDiv.style.left = '0';
    connectionStatusDiv.style.width = '100%';
    connectionStatusDiv.style.height = '30px';
    connectionStatusDiv.style.backgroundColor = 'red';
    connectionStatusDiv.style.color = 'white';
    connectionStatusDiv.style.textAlign = 'center';
    connectionStatusDiv.style.lineHeight = '30px';
    connectionStatusDiv.style.zIndex = '9999';
    connectionStatusDiv.style.display = 'none'; // Initially hide it

    // Append the div to the body
    document.body.appendChild(connectionStatusDiv);

    // Function to perform the XMLHttpRequest and handle the response
    const checkConnectionInternal = function () {
        const xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                const myObj = JSON.parse(this.responseText);
                if (myObj.id == id) {
                    console.log(myObj.connected);

                    // Show or hide the sticky red rectangle based on connection status
                    if (!myObj.connected) {
                        connectionStatusDiv.innerHTML = 'Connection Lost for '+myObj.id;
                        connectionStatusDiv.style.display = 'block';
                    } else {
                        connectionStatusDiv.style.display = 'none';
                    }
                }
            }
        }

        xmlhttp.open('POST', '../controlData/controlconnection.php', true);
        xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
        xmlhttp.send('id=' + id);
    }

    // Call the function initially
    checkConnectionInternal();

    // Set up an interval to call the function every 1000 milliseconds (1 second)
    setInterval(checkConnectionInternal, 1000);
}
