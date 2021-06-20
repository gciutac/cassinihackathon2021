$(document).ready(function () {
    setInterval(function () {
        fetchData()
    }, 1000)
  })

  const fetchData = () => {
    fetch('http://5.189.160.203:8110/api/esp/name/RGB?type=RGB', {
        method: 'GET',
        headers: {
          'x-device-token': 'Vh7X5JSkoxRSsyf8fgur2jZwt-sIdIYp',
        }
      })
      .then(response => response.json())
      .then(data => {
        console.log('Success:', data);
        triggerAction(data)
      })
      .catch((error) => {
        console.error('Error:', error)
      })
  }

  const triggerAction = (data) => {
      if(data.val1 == 1){
        $("body").css("background-color","red")
      } else if(data.val2 == 1){
        $("body").css("background-color","green")
      }
      else {
        $("body").css("background-color","blue")
      }
  }


