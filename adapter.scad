stepperShaftDiameter = 6.4;
stepperShaftLength = 10;
routerShaftDiameter = 10;
routerShaftLength = 20;
outerDiameter = 18;
		  
difference() {
    cylinder(r = outerDiameter / 2, h = stepperShaftLength + routerShaftLength);
    translate([0, 0, -1])
        union() {
            cylinder(r = stepperShaftDiameter / 2, h = 2 + stepperShaftLength + routerShaftLength);
            cylinder(r = routerShaftDiameter / 2, h = 2 + routerShaftLength);
            translate([routerShaftDiameter / 2 - 2.5/2, -4/2, 0])
                cube([2.5, 4, routerShaftLength]);
	}
}
