#!/usr/bin/env python3
"""
Shape Geometry Visualizer
Creates interactive HTML visualization of geometric shapes
"""

import matplotlib.pyplot as plt
import numpy as np
import json
from matplotlib.patches import Rectangle, Circle
from mpl_toolkits.mplot3d import Axes3D
import argparse

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
                    area = np.pi * radius**2
                    volume = 0
                    shapes.append({
                        'type': 'Circle',
                        'radius': radius,
                        'area': area,
                        'volume': volume
                    })
                    
                elif shape_type == "Sphere":
                    radius = float(line[1])
                    area = 4 * np.pi * radius**2
                    volume = (4/3) * np.pi * radius**3
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

def create_2d_visualization(shapes):
    """Create 2D visualization of shapes"""
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 12))
    fig.suptitle('Shape Geometry Analysis - 2D Visualization', fontsize=16, fontweight='bold')
    
    # Plot 1: Individual shapes (2D only)
    ax1.set_title('2D Shapes Layout')
    ax1.set_xlim(-1, 15)
    ax1.set_ylim(-1, 10)
    ax1.set_aspect('equal')
    ax1.grid(True, alpha=0.3)
    
    x_offset = 0
    colors = ['red', 'blue', 'green', 'orange', 'purple', 'brown', 'pink', 'gray']
    
    for i, shape in enumerate(shapes):
        color = colors[i % len(colors)]
        
        if shape['type'] == 'Rectangle':
            rect = Rectangle((x_offset, 2), shape['width'], shape['length'], 
                           facecolor=color, alpha=0.6, edgecolor='black')
            ax1.add_patch(rect)
            ax1.text(x_offset + shape['width']/2, 2 + shape['length']/2, 
                    f"Rect {i+1}\n{shape['width']}×{shape['length']}", 
                    ha='center', va='center', fontsize=8, fontweight='bold')
            x_offset += shape['width'] + 1
            
        elif shape['type'] == 'Circle':
            circle = Circle((x_offset + shape['radius'], 5), shape['radius'], 
                          facecolor=color, alpha=0.6, edgecolor='black')
            ax1.add_patch(circle)
            ax1.text(x_offset + shape['radius'], 5, 
                    f"Circle {i+1}\nr={shape['radius']:.1f}", 
                    ha='center', va='center', fontsize=8, fontweight='bold')
            x_offset += 2 * shape['radius'] + 1
    
    # Plot 2: Area comparison
    ax2.set_title('Area Comparison')
    shape_names = [f"{shape['type']} {i+1}" for i, shape in enumerate(shapes)]
    areas = [shape['area'] for shape in shapes]
    bars = ax2.bar(range(len(shapes)), areas, color=colors[:len(shapes)], alpha=0.7)
    ax2.set_xlabel('Shapes')
    ax2.set_ylabel('Area (square units)')
    ax2.set_xticks(range(len(shapes)))
    ax2.set_xticklabels(shape_names, rotation=45, ha='right')
    
    # Add value labels on bars
    for bar, area in zip(bars, areas):
        height = bar.get_height()
        ax2.text(bar.get_x() + bar.get_width()/2., height + height*0.01,
                f'{area:.2f}', ha='center', va='bottom', fontsize=9)
    
    # Plot 3: Volume comparison
    ax3.set_title('Volume Comparison')
    volumes = [shape['volume'] for shape in shapes]
    bars = ax3.bar(range(len(shapes)), volumes, color=colors[:len(shapes)], alpha=0.7)
    ax3.set_xlabel('Shapes')
    ax3.set_ylabel('Volume (cubic units)')
    ax3.set_xticks(range(len(shapes)))
    ax3.set_xticklabels(shape_names, rotation=45, ha='right')
    
    # Add value labels on bars
    for bar, volume in zip(bars, volumes):
        height = bar.get_height()
        if height > 0:
            ax3.text(bar.get_x() + bar.get_width()/2., height + height*0.01,
                    f'{volume:.2f}', ha='center', va='bottom', fontsize=9)
    
    # Plot 4: Shape distribution pie chart
    ax4.set_title('Shape Type Distribution')
    shape_types = {}
    for shape in shapes:
        shape_types[shape['type']] = shape_types.get(shape['type'], 0) + 1
    
    labels = list(shape_types.keys())
    sizes = list(shape_types.values())
    colors_pie = ['gold', 'lightcoral', 'lightskyblue', 'lightgreen']
    
    wedges, texts, autotexts = ax4.pie(sizes, labels=labels, colors=colors_pie[:len(labels)], 
                                      autopct='%1.1f%%', startangle=90)
    
    plt.tight_layout()
    plt.savefig('shape_analysis_2d.png', dpi=300, bbox_inches='tight')
    plt.show()

def create_3d_visualization(shapes):
    """Create 3D visualization for 3D shapes"""
    fig = plt.figure(figsize=(15, 10))
    
    # Create subplots for 3D shapes
    sphere_shapes = [s for s in shapes if s['type'] == 'Sphere']
    prism_shapes = [s for s in shapes if s['type'] == 'RectPrism']
    
    if sphere_shapes or prism_shapes:
        if sphere_shapes and prism_shapes:
            ax1 = fig.add_subplot(121, projection='3d')
            ax2 = fig.add_subplot(122, projection='3d')
        else:
            ax1 = fig.add_subplot(111, projection='3d')
            ax2 = None
        
        # Plot spheres
        if sphere_shapes:
            ax1.set_title('Spheres - 3D Visualization')
            
            for i, sphere in enumerate(sphere_shapes):
                # Create sphere
                u = np.linspace(0, 2 * np.pi, 20)
                v = np.linspace(0, np.pi, 20)
                r = sphere['radius']
                
                x = r * np.outer(np.cos(u), np.sin(v)) + i * 3 * r
                y = r * np.outer(np.sin(u), np.sin(v))
                z = r * np.outer(np.ones(np.size(u)), np.cos(v))
                
                ax1.plot_surface(x, y, z, alpha=0.6, 
                               color=plt.cm.viridis(i / len(sphere_shapes)))
                
                # Add label
                ax1.text(i * 3 * r, 0, r + 0.5, f'Sphere {i+1}\nr={r:.1f}', 
                        fontsize=10, ha='center')
            
            ax1.set_xlabel('X')
            ax1.set_ylabel('Y')
            ax1.set_zlabel('Z')
        
        # Plot rectangular prisms
        if prism_shapes and ax2:
            ax2.set_title('Rectangular Prisms - 3D Visualization')
            
            for i, prism in enumerate(prism_shapes):
                # Create rectangular prism
                w, l, h = prism['width'], prism['length'], prism['height']
                
                # Define vertices
                x_offset = i * (w + 2)
                vertices = [
                    [x_offset, 0, 0], [x_offset + w, 0, 0], [x_offset + w, l, 0], [x_offset, l, 0],  # bottom
                    [x_offset, 0, h], [x_offset + w, 0, h], [x_offset + w, l, h], [x_offset, l, h]   # top
                ]
                
                # Define faces
                faces = [
                    [vertices[0], vertices[1], vertices[2], vertices[3]],  # bottom
                    [vertices[4], vertices[5], vertices[6], vertices[7]],  # top
                    [vertices[0], vertices[1], vertices[5], vertices[4]],  # front
                    [vertices[2], vertices[3], vertices[7], vertices[6]],  # back
                    [vertices[1], vertices[2], vertices[6], vertices[5]],  # right
                    [vertices[4], vertices[7], vertices[3], vertices[0]]   # left
                ]
                
                # Plot faces
                from mpl_toolkits.mplot3d.art3d import Poly3DCollection
                face_colors = plt.cm.plasma(i / len(prism_shapes))
                ax2.add_collection3d(Poly3DCollection(faces, alpha=0.6, 
                                                    facecolor=face_colors, edgecolor='black'))
                
                # Add label
                ax2.text(x_offset + w/2, l/2, h + 0.5, 
                        f'Prism {i+1}\n{w}×{l}×{h}', 
                        fontsize=10, ha='center')
            
            ax2.set_xlabel('X')
            ax2.set_ylabel('Y')
            ax2.set_zlabel('Z')
    
    plt.tight_layout()
    plt.savefig('shape_analysis_3d.png', dpi=300, bbox_inches='tight')
    plt.show()

def generate_html_report(shapes):
    """Generate an HTML report with analysis"""
    
    total_area = sum(shape['area'] for shape in shapes)
    total_volume = sum(shape['volume'] for shape in shapes)
    max_area = max(shape['area'] for shape in shapes)
    max_volume = max(shape['volume'] for shape in shapes)
    
    html_content = f"""
    <!DOCTYPE html>
    <html>
    <head>
        <title>Shape Geometry Analysis Report</title>
        <style>
            body {{ font-family: Arial, sans-serif; margin: 40px; background-color: #f5f5f5; }}
            .container {{ max-width: 1200px; margin: 0 auto; background-color: white; padding: 30px; border-radius: 10px; box-shadow: 0 0 20px rgba(0,0,0,0.1); }}
            h1 {{ color: #2c3e50; text-align: center; border-bottom: 3px solid #3498db; padding-bottom: 10px; }}
            h2 {{ color: #34495e; border-left: 4px solid #3498db; padding-left: 15px; }}
            .shape-grid {{ display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; margin: 20px 0; }}
            .shape-card {{ background-color: #ecf0f1; padding: 20px; border-radius: 8px; border-left: 4px solid #3498db; }}
            .stats {{ background-color: #e8f6f3; padding: 20px; border-radius: 8px; margin: 20px 0; }}
            .highlight {{ background-color: #fff3cd; padding: 15px; border-radius: 5px; border-left: 4px solid #ffc107; margin: 10px 0; }}
            table {{ width: 100%; border-collapse: collapse; margin: 20px 0; }}
            th, td {{ padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }}
            th {{ background-color: #3498db; color: white; }}
            .concept {{ background-color: #f8f9fa; padding: 15px; margin: 10px 0; border-radius: 5px; border-left: 4px solid #28a745; }}
        </style>
    </head>
    <body>
        <div class="container">
            <h1>🔷 Shape Geometry Analysis Report 🔷</h1>
            
            <div class="stats">
                <h2>📊 Summary Statistics</h2>
                <p><strong>Total Shapes Analyzed:</strong> {len(shapes)}</p>
                <p><strong>Total Combined Area:</strong> {total_area:.3f} square units</p>
                <p><strong>Total Combined Volume:</strong> {total_volume:.3f} cubic units</p>
                <p><strong>Average Area per Shape:</strong> {total_area/len(shapes):.3f} square units</p>
                <p><strong>Average Volume per Shape:</strong> {total_volume/len(shapes):.3f} cubic units</p>
            </div>
            
            <div class="highlight">
                <h3>🏆 Maximum Values</h3>
                <p><strong>Largest Area:</strong> {max_area:.3f} square units</p>
                <p><strong>Largest Volume:</strong> {max_volume:.3f} cubic units</p>
            </div>
            
            <h2>📋 Detailed Shape Information</h2>
            <table>
                <tr>
                    <th>#</th>
                    <th>Shape Type</th>
                    <th>Dimensions</th>
                    <th>Area</th>
                    <th>Volume</th>
                </tr>
    """
    
    for i, shape in enumerate(shapes, 1):
        if shape['type'] == 'Rectangle':
            dimensions = f"{shape['width']} × {shape['length']}"
        elif shape['type'] == 'Circle':
            dimensions = f"radius = {shape['radius']}"
        elif shape['type'] == 'Sphere':
            dimensions = f"radius = {shape['radius']}"
        elif shape['type'] == 'RectPrism':
            dimensions = f"{shape['width']} × {shape['length']} × {shape['height']}"
        
        html_content += f"""
                <tr>
                    <td>{i}</td>
                    <td>{shape['type']}</td>
                    <td>{dimensions}</td>
                    <td>{shape['area']:.3f}</td>
                    <td>{shape['volume']:.3f}</td>
                </tr>
        """
    
    html_content += """
            </table>
            
            <h2>🎓 Educational Concepts Demonstrated</h2>
            
            <div class="concept">
                <h3>Object-Oriented Programming (OOP)</h3>
                <p>This program showcases inheritance, polymorphism, encapsulation, and abstraction through the Shape class hierarchy.</p>
            </div>
            
            <div class="concept">
                <h3>Template Programming</h3>
                <p>The Rectangle class uses templates, allowing it to work with different data types (int, double, etc.).</p>
            </div>
            
            <div class="concept">
                <h3>Operator Overloading</h3>
                <p>Addition (+) and subtraction (-) operators are overloaded to perform meaningful operations on shapes.</p>
            </div>
            
            <div class="concept">
                <h3>Dynamic Memory Management</h3>
                <p>Uses pointers and dynamic allocation to manage shape objects polymorphically.</p>
            </div>
            
            <div class="concept">
                <h3>STL Containers</h3>
                <p>Utilizes std::list for efficient shape storage and iteration.</p>
            </div>
            
            <h2>🌟 Real-World Applications</h2>
            <div class="shape-grid">
                <div class="shape-card">
                    <h3>🎮 Game Development</h3>
                    <p>Collision detection, object management, and physics calculations.</p>
                </div>
                <div class="shape-card">
                    <h3>🏗️ Architecture & Construction</h3>
                    <p>Area and volume calculations for material estimation and space planning.</p>
                </div>
                <div class="shape-card">
                    <h3>🖥️ Computer Graphics</h3>
                    <p>Shape representation, transformation, and rendering.</p>
                </div>
                <div class="shape-card">
                    <h3>🏭 Manufacturing</h3>
                    <p>Material usage optimization and production planning.</p>
                </div>
            </div>
            
            <div class="stats">
                <h2>💡 Key Takeaways</h2>
                <ul>
                    <li>Object-oriented design enables code reusability and maintainability</li>
                    <li>Polymorphism allows treating different shapes uniformly</li>
                    <li>Template programming provides type flexibility</li>
                    <li>Operator overloading makes code more intuitive and readable</li>
                    <li>Virtual functions enable dynamic method dispatch</li>
                </ul>
            </div>
        </div>
    </body>
    </html>
    """
    
    with open('shape_analysis_report.html', 'w') as f:
        f.write(html_content)
    
    print("HTML report generated: shape_analysis_report.html")

def main():
    parser = argparse.ArgumentParser(description='Visualize shape geometry data')
    parser.add_argument('filename', help='Input file containing shape data')
    args = parser.parse_args()
    
    shapes = parse_shapes_file(args.filename)
    
    if not shapes:
        print("No shapes found or error reading file!")
        return
    
    print(f"Loaded {len(shapes)} shapes from {args.filename}")
    
    # Create visualizations
    print("Creating 2D visualization...")
    create_2d_visualization(shapes)
    
    print("Creating 3D visualization...")
    create_3d_visualization(shapes)
    
    print("Generating HTML report...")
    generate_html_report(shapes)
    
    print("All visualizations complete!")
    print("Files generated:")
    print("- shape_analysis_2d.png")
    print("- shape_analysis_3d.png") 
    print("- shape_analysis_report.html")

if __name__ == "__main__":
    main()
