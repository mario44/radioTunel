<script>
function getTime(){
var dt = new Date();
let czas = dt.toLocaleTimeString();
//setTimeout(function(){getTime();},60000); 
console.log(czas);
} 
getTime();
</script>
