#!/usr/bin/env python3
"""
Simple Shape Analysis and HTML Report Generator
No external dependencies required
"""

import math
import sys

def parse_shapes_file(filename):
    """Parse the shapes input file and return shape data"""
    shapes = []
    
    try:
        with open(filename, 'r') as f:
            num_shapes = int(f.readline().strip())
            
            for _ in range(num_shapes):
                line = f.readline().strip().split()
                shape_type = line[0]
                
                if shape_type == "Rectangle":
                    width, length = float(line[1]), float(line[2])
                    area = width * length
                    volume = 0
                    shapes.append({
                        'type': 'Rectangle',
                        'width': width,
                        'length': length,
                        'area': area,
                        'volume': volume
                    })
                    
                elif shape_type == "Circle":
                    radius = float(line[1])
                    area = math.pi * radius**2
                    volume = 0
                    shapes.append({
                        'type': 'Circle',
                        'radius': radius,
                        'area': area,
                        'volume': volume
                    })
                    
                elif shape_type == "Sphere":
                    radius = float(line[1])
                    area = 4 * math.pi * radius**2
                    volume = (4/3) * math.pi * radius**3
                    shapes.append({
                        'type': 'Sphere',
                        'radius': radius,
                        'area': area,
                        'volume': volume
                    })
                    
                elif shape_type == "RectPrism":
                    width, length, height = float(line[1]), float(line[2]), float(line[3])
                    area = 2 * (width*length + width*height + length*height)
                    volume = width * length * height
                    shapes.append({
                        'type': 'RectPrism',
                        'width': width,
                        'length': length,
                        'height': height,
                        'area': area,
                        'volume': volume
                    })
                    
    except FileNotFoundError:
        print(f"Error: File {filename} not found!")
        return []
    except Exception as e:
        print(f"Error parsing file: {e}")
        return []
        
    return shapes

def create_text_charts(shapes):
    """Create simple ASCII bar charts"""
    print("\n" + "="*80)
    print("                        ASCII BAR CHARTS")
    print("="*80)
    
    # Area chart
    print("\nArea Comparison (each ■ = ~10 square units):")
    print("-" * 50)
    max_area = max(shape['area'] for shape in shapes)
    scale = max_area / 50  # Scale to fit in 50 characters
    
    for i, shape in enumerate(shapes, 1):
        area = shape['area']
        bars = int(area / scale) if scale > 0 else 0
        bar_str = "■" * bars
        print(f"{i:2d}. {shape['type']:10s} │{bar_str:<50} {area:8.2f}")
    
    # Volume chart
    print("\nVolume Comparison (each ▲ = ~20 cubic units):")
    print("-" * 50)
    volumes = [shape['volume'] for shape in shapes if shape['volume'] > 0]
    if volumes:
        max_volume = max(volumes)
        scale = max_volume / 50
        
        for i, shape in enumerate(shapes, 1):
            volume = shape['volume']
            if volume > 0:
                bars = int(volume / scale) if scale > 0 else 0
                bar_str = "▲" * bars
                print(f"{i:2d}. {shape['type']:10s} │{bar_str:<50} {volume:8.2f}")

def generate_comprehensive_html_report(shapes):
    """Generate a comprehensive HTML report with analysis"""
    
    total_area = sum(shape['area'] for shape in shapes)
    total_volume = sum(shape['volume'] for shape in shapes)
    max_area = max(shape['area'] for shape in shapes)
    max_volume = max(shape['volume'] for shape in shapes)
    
    # Shape type distribution
    shape_counts = {}
    for shape in shapes:
        shape_counts[shape['type']] = shape_counts.get(shape['type'], 0) + 1
    
    html_content = f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Shape Geometry Analysis Report</title>
        <style>
            * {{ margin: 0; padding: 0; box-sizing: border-box; }}
            body {{ 
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
                line-height: 1.6; 
                color: #333;
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                min-height: 100vh;
                padding: 20px;
            }}
            .container {{ 
                max-width: 1200px; 
                margin: 0 auto; 
                background: white; 
                border-radius: 15px; 
                box-shadow: 0 20px 40px rgba(0,0,0,0.1);
                overflow: hidden;
            }}
            .header {{
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                color: white;
                text-align: center;
                padding: 40px 20px;
            }}
            .header h1 {{ 
                font-size: 2.5em; 
                margin-bottom: 10px;
                text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
            }}
            .content {{ padding: 40px; }}
            h2 {{ 
                color: #4a5568; 
                border-bottom: 3px solid #667eea; 
                padding-bottom: 10px; 
                margin-bottom: 20px;
                font-size: 1.8em;
            }}
            h3 {{ 
                color: #2d3748; 
                margin-top: 25px; 
                margin-bottom: 15px;
                font-size: 1.3em;
            }}
            .stats-grid {{ 
                display: grid; 
                grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); 
                gap: 20px; 
                margin: 30px 0; 
            }}
            .stat-card {{ 
                background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
                color: white;
                padding: 25px; 
                border-radius: 10px; 
                text-align: center;
                box-shadow: 0 5px 15px rgba(0,0,0,0.1);
                transition: transform 0.3s ease;
            }}
            .stat-card:hover {{ transform: translateY(-5px); }}
            .stat-number {{ font-size: 2.2em; font-weight: bold; display: block; }}
            .stat-label {{ font-size: 0.9em; opacity: 0.9; }}
            .shape-table {{ 
                width: 100%; 
                border-collapse: collapse; 
                margin: 20px 0;
                background: white;
                border-radius: 10px;
                overflow: hidden;
                box-shadow: 0 5px 15px rgba(0,0,0,0.1);
            }}
            .shape-table th {{ 
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                color: white; 
                padding: 15px 12px; 
                text-align: left;
                font-weight: 600;
            }}
            .shape-table td {{ 
                padding: 12px; 
                border-bottom: 1px solid #e2e8f0;
                transition: background-color 0.3s ease;
            }}
            .shape-table tr:hover td {{ background-color: #f7fafc; }}
            .shape-table tr:nth-child(even) {{ background-color: #f8f9fa; }}
            .highlight {{ 
                background: linear-gradient(135deg, #ffecd2 0%, #fcb69f 100%);
                padding: 20px; 
                border-radius: 10px; 
                margin: 20px 0;
                border-left: 5px solid #ff6b6b;
            }}
            .concept-grid {{ 
                display: grid; 
                grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); 
                gap: 20px; 
                margin: 30px 0; 
            }}
            .concept-card {{ 
                background: #f8f9fa; 
                padding: 25px; 
                border-radius: 10px; 
                border-left: 5px solid #28a745;
                box-shadow: 0 3px 10px rgba(0,0,0,0.1);
                transition: transform 0.3s ease;
            }}
            .concept-card:hover {{ transform: translateY(-3px); }}
            .app-grid {{ 
                display: grid; 
                grid-template-columns: repeat(auto-fit, minmax(280px, 1fr)); 
                gap: 20px; 
                margin: 30px 0; 
            }}
            .app-card {{ 
                background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%);
                padding: 25px; 
                border-radius: 10px;
                text-align: center;
                box-shadow: 0 5px 15px rgba(0,0,0,0.1);
                transition: transform 0.3s ease;
            }}
            .app-card:hover {{ transform: translateY(-5px); }}
            .app-icon {{ font-size: 2.5em; margin-bottom: 15px; }}
            .formula {{ 
                background: #f1f5f9; 
                padding: 15px; 
                border-radius: 8px; 
                font-family: 'Courier New', monospace;
                margin: 10px 0;
                border-left: 4px solid #3b82f6;
            }}
            .bar-chart {{ 
                margin: 20px 0; 
                padding: 20px; 
                background: #f8f9fa; 
                border-radius: 10px;
            }}
            .bar {{ 
                display: flex; 
                align-items: center; 
                margin: 8px 0; 
                font-size: 14px;
            }}
            .bar-label {{ 
                width: 120px; 
                font-weight: bold; 
                color: #4a5568;
            }}
            .bar-fill {{ 
                height: 25px; 
                background: linear-gradient(90deg, #667eea, #764ba2);
                margin-right: 10px; 
                border-radius: 3px;
                display: flex;
                align-items: center;
                justify-content: flex-end;
                padding-right: 8px;
                color: white;
                font-weight: bold;
                font-size: 12px;
            }}
            .footer {{
                background: #2d3748;
                color: white;
                text-align: center;
                padding: 30px;
                margin-top: 40px;
            }}
            @media (max-width: 768px) {{
                .container {{ margin: 10px; }}
                .content {{ padding: 20px; }}
                .stats-grid {{ grid-template-columns: 1fr; }}
                .concept-grid {{ grid-template-columns: 1fr; }}
                .app-grid {{ grid-template-columns: 1fr; }}
            }}
        </style>
    </head>
    <body>
        <div class="container">
            <div class="header">
                <h1>🔷 Shape Geometry Analysis Report 🔷</h1>
                <p>Comprehensive Analysis of Geometric Shapes and Their Properties</p>
            </div>
            
            <div class="content">
                <h2>📊 Executive Summary</h2>
                <div class="stats-grid">
                    <div class="stat-card">
                        <span class="stat-number">{len(shapes)}</span>
                        <span class="stat-label">Total Shapes</span>
                    </div>
                    <div class="stat-card">
                        <span class="stat-number">{total_area:.1f}</span>
                        <span class="stat-label">Total Area (sq units)</span>
                    </div>
                    <div class="stat-card">
                        <span class="stat-number">{total_volume:.1f}</span>
                        <span class="stat-label">Total Volume (cu units)</span>
                    </div>
                    <div class="stat-card">
                        <span class="stat-number">{total_area/len(shapes):.1f}</span>
                        <span class="stat-label">Avg Area per Shape</span>
                    </div>
                </div>
                
                <div class="highlight">
                    <h3>🏆 Maximum Values</h3>
                    <p><strong>Largest Area:</strong> {max_area:.3f} square units</p>
                    <p><strong>Largest Volume:</strong> {max_volume:.3f} cubic units</p>
                </div>
    """
    
    # Add bar charts
    html_content += """
                <h2>📈 Visual Analysis</h2>
                <div class="bar-chart">
                    <h3>Area Comparison</h3>
    """
    
    max_area_for_chart = max(shape['area'] for shape in shapes)
    for i, shape in enumerate(shapes, 1):
        width_percent = (shape['area'] / max_area_for_chart) * 100 if max_area_for_chart > 0 else 0
        html_content += f"""
                    <div class="bar">
                        <div class="bar-label">{shape['type']} {i}</div>
                        <div class="bar-fill" style="width: {width_percent:.1f}%">{shape['area']:.1f}</div>
                    </div>
        """
    
    html_content += """
                </div>
                
                <div class="bar-chart">
                    <h3>Volume Comparison</h3>
    """
    
    max_volume_for_chart = max(shape['volume'] for shape in shapes if shape['volume'] > 0)
    for i, shape in enumerate(shapes, 1):
        if shape['volume'] > 0:
            width_percent = (shape['volume'] / max_volume_for_chart) * 100 if max_volume_for_chart > 0 else 0
            html_content += f"""
                        <div class="bar">
                            <div class="bar-label">{shape['type']} {i}</div>
                            <div class="bar-fill" style="width: {width_percent:.1f}%">{shape['volume']:.1f}</div>
                        </div>
            """
    
    html_content += """
                </div>
    """
    
    # Detailed shape table
    html_content += """
                <h2>📋 Detailed Shape Information</h2>
                <table class="shape-table">
                    <thead>
                        <tr>
                            <th>#</th>
                            <th>Shape Type</th>
                            <th>Dimensions</th>
                            <th>Area (sq units)</th>
                            <th>Volume (cu units)</th>
                            <th>Formulas Used</th>
                        </tr>
                    </thead>
                    <tbody>
    """
    
    for i, shape in enumerate(shapes, 1):
        if shape['type'] == 'Rectangle':
            dimensions = f"{shape['width']} × {shape['length']}"
            formulas = "Area = w×l"
        elif shape['type'] == 'Circle':
            dimensions = f"radius = {shape['radius']}"
            formulas = "Area = πr²"
        elif shape['type'] == 'Sphere':
            dimensions = f"radius = {shape['radius']}"
            formulas = "Area = 4πr², Volume = (4/3)πr³"
        elif shape['type'] == 'RectPrism':
            dimensions = f"{shape['width']} × {shape['length']} × {shape['height']}"
            formulas = "Area = 2(wl+wh+lh), Volume = w×l×h"
        
        html_content += f"""
                        <tr>
                            <td>{i}</td>
                            <td>{shape['type']}</td>
                            <td>{dimensions}</td>
                            <td>{shape['area']:.3f}</td>
                            <td>{shape['volume']:.3f}</td>
                            <td><small>{formulas}</small></td>
                        </tr>
        """
    
    html_content += """
                    </tbody>
                </table>
                
                <h2>🎓 Educational Concepts Demonstrated</h2>
                <div class="concept-grid">
                    <div class="concept-card">
                        <h3>🏗️ Object-Oriented Programming</h3>
                        <p><strong>Inheritance:</strong> All shapes inherit from base Shape class</p>
                        <p><strong>Polymorphism:</strong> Virtual functions enable different implementations</p>
                        <p><strong>Encapsulation:</strong> Private data with public interfaces</p>
                        <p><strong>Abstraction:</strong> Common interface for different shapes</p>
                    </div>
                    
                    <div class="concept-card">
                        <h3>🔧 Template Programming</h3>
                        <p>Rectangle class uses templates for type flexibility</p>
                        <p>Demonstrates generic programming concepts</p>
                        <p>Compile-time type safety and optimization</p>
                    </div>
                    
                    <div class="concept-card">
                        <h3>⚡ Operator Overloading</h3>
                        <p>Addition (+) and subtraction (-) operators redefined</p>
                        <p>Makes code more intuitive and readable</p>
                        <p>Extends language functionality naturally</p>
                    </div>
                    
                    <div class="concept-card">
                        <h3>🧠 Memory Management</h3>
                        <p>Dynamic allocation with new/delete</p>
                        <p>Polymorphic behavior through base pointers</p>
                        <p>Resource management principles</p>
                    </div>
                    
                    <div class="concept-card">
                        <h3>📚 STL Usage</h3>
                        <p>std::list for dynamic container management</p>
                        <p>Iterator-based traversal patterns</p>
                        <p>Standard library integration</p>
                    </div>
                    
                    <div class="concept-card">
                        <h3>📐 Mathematical Programming</h3>
                        <p>Implementation of geometric formulas</p>
                        <p>Precision handling with floating-point</p>
                        <p>Mathematical constant usage (π)</p>
                    </div>
                </div>
                
                <h2>🌍 Real-World Applications</h2>
                <div class="app-grid">
                    <div class="app-card">
                        <div class="app-icon">🎮</div>
                        <h3>Game Development</h3>
                        <p>Collision detection, physics engines, object management, and spatial optimization for interactive entertainment.</p>
                    </div>
                    
                    <div class="app-card">
                        <div class="app-icon">🏗️</div>
                        <h3>Architecture & Construction</h3>
                        <p>Area calculations for flooring, volume estimates for concrete, and space planning for building design.</p>
                    </div>
                    
                    <div class="app-card">
                        <div class="app-icon">🖥️</div>
                        <h3>Computer Graphics</h3>
                        <p>3D modeling, ray tracing, shape tessellation, and rendering pipeline optimization.</p>
                    </div>
                    
                    <div class="app-card">
                        <div class="app-icon">🏭</div>
                        <h3>Manufacturing</h3>
                        <p>Material usage calculation, production optimization, and quality control measurements.</p>
                    </div>
                    
                    <div class="app-card">
                        <div class="app-icon">📱</div>
                        <h3>Mobile Apps</h3>
                        <p>UI layout calculations, touch area optimization, and responsive design implementations.</p>
                    </div>
                    
                    <div class="app-card">
                        <div class="app-icon">🚗</div>
                        <h3>Automotive Design</h3>
                        <p>Aerodynamic analysis, interior space optimization, and component volume calculations.</p>
                    </div>
                </div>
                
                <h2>📝 Mathematical Formulas Reference</h2>
                <div class="concept-grid">
                    <div class="concept-card">
                        <h3>Rectangle Formulas</h3>
                        <div class="formula">Area = width × length</div>
                        <div class="formula">Volume = 0 (2D shape)</div>
                    </div>
                    
                    <div class="concept-card">
                        <h3>Circle Formulas</h3>
                        <div class="formula">Area = π × radius²</div>
                        <div class="formula">Volume = 0 (2D shape)</div>
                    </div>
                    
                    <div class="concept-card">
                        <h3>Sphere Formulas</h3>
                        <div class="formula">Surface Area = 4π × radius²</div>
                        <div class="formula">Volume = (4/3)π × radius³</div>
                    </div>
                    
                    <div class="concept-card">
                        <h3>Rectangular Prism Formulas</h3>
                        <div class="formula">Surface Area = 2(wl + wh + lh)</div>
                        <div class="formula">Volume = width × length × height</div>
                    </div>
                </div>
                
                <h2>💡 Key Learning Outcomes</h2>
                <div class="highlight">
                    <ul style="list-style-type: none; padding-left: 0;">
                        <li>✅ <strong>OOP Mastery:</strong> Understanding inheritance, polymorphism, and encapsulation</li>
                        <li>✅ <strong>Generic Programming:</strong> Template usage for flexible, reusable code</li>
                        <li>✅ <strong>Memory Management:</strong> Dynamic allocation and pointer manipulation</li>
                        <li>✅ <strong>Mathematical Programming:</strong> Implementing geometric calculations</li>
                        <li>✅ <strong>Software Design:</strong> Clean interfaces and separation of concerns</li>
                        <li>✅ <strong>Problem Solving:</strong> Breaking complex problems into manageable components</li>
                    </ul>
                </div>
            </div>
            
            <div class="footer">
                <p>Generated by Shape Geometry Analysis System</p>
                <p>Demonstrating Computer Science Fundamentals Through Practical Applications</p>
            </div>
        </div>
    </body>
    </html>
    """
    
    with open('comprehensive_shape_report.html', 'w', encoding='utf-8') as f:
        f.write(html_content)
    
    print("Comprehensive HTML report generated: comprehensive_shape_report.html")

def main():
    if len(sys.argv) != 2:
        print("Usage: python simple_analyzer.py <input_file>")
        return
    
    filename = sys.argv[1]
    shapes = parse_shapes_file(filename)
    
    if not shapes:
        print("No shapes found or error reading file!")
        return
    
    print(f"Loaded {len(shapes)} shapes from {filename}")
    
    # Create text-based charts
    create_text_charts(shapes)
    
    # Generate comprehensive HTML report
    generate_comprehensive_html_report(shapes)
    
    print(f"\nAnalysis complete!")
    print(f"- Text charts displayed above")
    print(f"- Comprehensive HTML report: comprehensive_shape_report.html")

if __name__ == "__main__":
    main()
