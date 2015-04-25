// Copyright 2011 Cliff L. Biffle.
// This file is licensed Creative Commons Attribution-ShareAlike 3.0.
// http://creativecommons.org/licenses/by-sa/3.0/

// You can get this file from http://www.thingiverse.com/thing:3575
use <parametric_involute_gear_v5.0.scad>

$vpr = [$t * 360, $t * 360, $t * 360];

// Couple handy arithmetic shortcuts
function sqr(n) = pow(n, 2);
function cube(n) = pow(n, 3);

routerShaftDiameter = 10;

// This was derived as follows:
// In Greg Frost's original script, the outer radius of a spur
// gear can be computed as...
function gear_outer_radius(number_of_teeth, circular_pitch) =
	(sqr(number_of_teeth) * sqr(circular_pitch) + 64800)
		/ (360 * number_of_teeth * circular_pitch);

// We can fit gears to the spacing by working it backwards.
//  spacing = gear_outer_radius(teeth1, cp)
//          + gear_outer_radius(teeth2, cp);
//
// I plugged this into an algebra system, assuming that spacing,
// teeth1, and teeth2 are given.  By solving for circular pitch,
// we get this terrifying equation:
function fit_spur_gears(n1, n2, spacing) =
	(180 * spacing * n1 * n2  +  180
		* sqrt(-(2*n1*cube(n2)-(sqr(spacing)-4)*sqr(n1)*sqr(n2)+2*cube(n1)*n2)))
	/ (n1*sqr(n2) + sqr(n1)*n2);

// Here's an example.
module example_gears() {
	n1 = 40; n2 = n1;
	p = fit_spur_gears(n1, n2, 60);
echo ("Pitch", p);
	// Simple Test:
difference() {
	gear (circular_pitch=p,
		gear_thickness = 5,
		rim_thickness = 5,
		hub_thickness = 5,
	    number_of_teeth = n1,
		circles=0,
                bore_diameter=10);
    translate([0, 0, -1])
        union() {
            cylinder(r = routerShaftDiameter / 2, h = 12);
            translate([routerShaftDiameter / 2 - 5/2, -5/2, 0])
                cube([5, 5, 12]);
	}
}
}
example_gears();
