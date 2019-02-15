
color("silver")import("D:/FM/Extras/stl/VE-096_NOZZLE_STEM.STL");
color("Goldenrod")import("D:/FM/Extras/stl/VE-097_NOZZLE.STL");



module open(){
   color("LightSlateGray")import("D:/FM/Extras/stl/TC2-060_NOZZLE_BLOCK.STL");
   color("LightGrey")import("D:/FM/Extras/stl/VE-050_M6_NUT.STL");
   color("gray")import("D:/FM/Extras/stl/MOLDED POSING.STL"); 
}

module closed(){
    color("LightSlateGray")import("D:/FM/Extras/stl/TC2-060_NOZZLE_BLOCK.STL");
    color("LightGrey")import("D:/FM/Extras/stl/VE-050_M6_NUT.STL");
    color("gray")import("D:/FM/Extras/stl/TC2-061_HEATER_BLOCK.STL");
    color("gray")import("D:/FM/Extras/stl/TC2-062_TRANSFER_BLOCK.STL");
}

module old(){
color("grey")import("D:/FM/Extras/stl/SQUARE BLOCK.STL");
color("lightgrey")import("D:/FM/Extras/stl/LOWER NUT.STL");    
}
    
//open();
closed();
//old();
