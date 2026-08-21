SVG svg("out.svg", -200, -200, 200, 200);
svg.color("lightgray");  // ↓ drawing x-y plane
svg.line(-200, 0, 200, 0); svg.line(0, -200, 0, 200);
svg.color("blue"); svg.line(10, 10, 80, 80);
svg.color("red"); svg.circle(50, 50, 1);
