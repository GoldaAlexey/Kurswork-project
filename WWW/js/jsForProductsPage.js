var expanded = false;
var arrayOfOpenDropdown = [0,0];
function showCheckboxes(number){
    if((number != arrayOfOpenDropdown[0]) && (expanded!=false)){
        var check = document.getElementById("checkboxes"+ arrayOfOpenDropdown[0]);
        check.style.display ="none";
        expanded = false;
        arrayOfOpenDropdown.splice(0,1);
    }
    var checkboxes = document.getElementById("checkboxes"+number);
    arrayOfOpenDropdown[0]=number;
    if(!expanded){
        checkboxes.style.display = "block";
        expanded = true;
    }
    else{
        checkboxes.style.display = "none";
        expanded = false;
    }
}