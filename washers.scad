pulleyholeradius=4.0/2;
mountholeradius=3.0/2;

or = 7.0/2;

difference()
{
   cylinder(r = or, h = 2);
   translate([0, 0, -1]) cylinder(r = pulleyholeradius, h = 4);
}

translate([10, 0, 0])
difference()
{
   cylinder(r = or, h = 4.5);
   translate([0, 0, -1]) cylinder(r = pulleyholeradius, h = 6);
}

translate([20, 0, 0])
difference()
{
   cylinder(r = 5, h = 6.5);
   translate([0, 0, -1]) cylinder(r = mountholeradius, h = 8);
}