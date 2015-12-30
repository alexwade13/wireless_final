
// Use Parse.Cloud.define to define as many cloud functions as you want.

function queryError(error) {
  console.log("Error: " + error.code + " " + error.message);
}

Parse.Cloud.afterSave("RawData", function(request) { 
  
  console.log(" Parse Status Update..");
 
  var myStatus = Parse.Object.extend("Status");
  var theStatus  = new myStatus();

  theStatus.set("equipmentID", "tread1");
   
  query = new Parse.Query("RawData");
  query.equalTo("sensor_type", "long_distance");
  query.descending("createdAt");

  query.first().then(function(results)
  {
    console.log("Getting long_distance values");
    if (results.get("Data")  < 27 && results.get("Data") > 4) 
    {
      console.log("Long_distance states In_Use");
      return true;
    } 
    else 
    {
      console.log("False - Long_distance");
      return false;
    }
  }, queryError).then(function(result){
    if (result == true) {
      theStatus.set("long_distance", true);
      console.log("setting the long distance status to be true");
    } else {
      theStatus.set("long_distance", false);
      console.log("setting the long distance status to be false");
    }

    return theStatus.save(null, {
      success: function(theStatus) {
        console.log('New status created with objectId: ' + theStatus.id);
      },
      error: function(gameScore, error) {
        console.log('Failed to create new status, with error code: ' + error.message);
      }
    });
  }, queryError).then(function(object) {
    query2 = new Parse.Query("RawData");
    query2.equalTo("sensor_type", "ultrasonic");
    query2.descending("createdAt");
    return query2.first();
  }, queryError).then(function(result){
    if (result.get("Data") < 27 && result.get("Data") > 4 ) {
      console.log("Ultrasonic states In_Use");
      return true;
    } else {
      console.log("False - ultrasonic");
      return false;
    }
  }, queryError).then(function(result) {
    if (result == true) {
      console.log("settting theStatus-ultrasonic, true");
      theStatus.set("ultrasonic", true);
    } else {
      console.log("settting theStatus-ultrasonic, false");
      theStatus.set("ultrasonic", false);
    }

    long_distance = theStatus.get("long_distance");
    ultrasonic = theStatus.get("ultrasonic");

    if (long_distance || ultrasonic) {
      theStatus.set("inUse", true);
    } else {
      theStatus.set("inUse", false);
    }

    return theStatus.save();
  }, queryError).then(function(object) {
    if (object != null) {
      console.log("Status saved correctly!");
    } else {
      console.log("Status not saved correctly!");
    }
  }, queryError);

});
