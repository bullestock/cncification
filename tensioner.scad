slotwidth=11.8;
height=15;
width=18;
pulleyholeoffset=7.5;
pulleyholeradius=4.0/2;
pulleyradius=16;
mountholeoffset=7.5;
mountholeradius=3.0/2;
springholeoffset=30;
springholedepth=5;
length=60;
skirt = 5;
union()
{
   translate([pulleyholeoffset+pulleyradius+skirt, -(width+2*skirt)/2, 0]) 
      cube([length-pulleyholeoffset-pulleyradius, width+2*skirt, 0.5]);
difference() {
   // Main form
   translate([0,-width/2, 0]) cube([length, width, height]);
   union() {
      // Gap
      translate([length-pulleyholeoffset-pulleyradius, -slotwidth/2, -1]) 
         cube([pulleyholeoffset+pulleyradius+1, slotwidth, height+2]);
      // Pulley hole
      rotate([90, 0, 0]) translate([length-pulleyholeoffset, height/2, -width/2-1]) 
         cylinder(r = pulleyholeradius, h = width+2);
      // Mount hole
      rotate([90, 0, 0]) translate([mountholeoffset, height/2, -width/2]) 
         cylinder(r = mountholeradius, h = width+2);
      // Spring hole
      translate([springholeoffset, 0, height-springholedepth]) rotate([0, 0, 90]) 
         cylinder(r = mountholeradius, h = springholedepth+1);
   }
}
}