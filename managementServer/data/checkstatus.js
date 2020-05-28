//https://github.com/fredEOF/arduinoWebpanel

function checkStatus() {
    allsensors = document.getElementsByClassName("sensor");
    for (let i = 0; i < allsensors.length; i++) {
        var checkbox = allsensors[i];
        getRequest(checkbox, true);
    }
}

function getRequest(checkbox) {
    var checkIp = new XMLHttpRequest();
    checkIp.open("GET", "http://" + checkbox.id + "/getState");
    checkIp.onerror = () => cancel();
    checkIp.ontimeout = () => cancel();

    checkIp.onload = () => {
        console.log(checkbox.id + " status is " + checkIp.responseText);
        if (checkIp.status >= 200 && checkIp.status < 400) {
            if (checkIp.responseText == "on" && !checkbox.checked) {
                checkbox.checked = true;
            }
            if (checkIp.responseText == "off" && checkbox.checked) {
                checkbox.checked = false;
            }
        }
    };

    function cancel() {
        checkIp.abort();
        checkbox.checked = false;
        console.log(checkbox.id + " not available!");
    }
    checkIp.timeout = 3000;
    checkIp.send();
}

function changeRequest(checkbox) {
    var setIp = new XMLHttpRequest();
    setIp.open("POST", "http://" + checkbox.id + "/changeState");
    setIp.ontimeout = () => setIp.abort();
    setIp.onerror = () => setIp.abort();
    setIp.send();
}

function changeState(checkbox) {
    changeRequest(checkbox);
    getRequest(checkbox);
}