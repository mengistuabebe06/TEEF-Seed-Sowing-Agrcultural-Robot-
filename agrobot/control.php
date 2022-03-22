  <?php
   $distance = $_POST['distance'];
   //echo $dist;
   //$distance =floatval($dist);
    require_once 'connect.php';

    $sql = "UPDATE sensorvalue SET ControlValue='$distance' WHERE SensorID = '1'";

    if (mysqli_query($conn, $sql) ) {
        $result["success"] = "1";
        $result["message"] = "success";

        echo json_encode($result);
        mysqli_close($conn);

    } else {

        $result["success"] = "0";
        $result["message"] = "error";

        echo json_encode($result);
        mysqli_close($conn);
    }
	?>