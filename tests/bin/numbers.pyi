<?xml version="1.0" ?>
<sdf version="1.6">
    <model name="DynamicObstacle">
      <pose>0 0 0.15 0 0 0</pose>
      <link name="link">
	<gravity>1</gravity>
        <inertial>
	  <inertia>
	    <ixx>0.17</ixx>
            <ixy>0.00</ixy>
            <ixz>0.00</ixz>
            <iyy>0.17</iyy>
            <iyz>0.00</iyz>
            <izz>0.17</izz>
          </inertia>
          <mass>100</mass>
        </inertial>
        <kinematic>false</kinematic>
        <collision name="collision">
          <max_contacts>0</max_contacts>
          <geometry>
            <box>
              <size>0.3 0.3 0.3</size>
            </box>
          </geometry>
	  <surface>
            <friction>
              <ode>
                <mu>0.0</mu>
                <mu2>0.0</mu2>
              </ode>
            </friction>
            <bounce>
              <restitution_coefficient>0.0</restitution_coefficient>
              <threshold>0.0</threshold>
      	  </bounce>
	  <contact>
            <ode>
              <kp>2000000000</kp>
	      <kd>1</kd>
              <max_vel>0.01</max_vel>
              <min_depth>0.00</min_depth>
            </ode>
          </contact>
          </surface>
        </collision>
        <visual name="visual">
          <geometry>
            <box>
              <size>0.3 0.3 0.3</size>
            </box>
          </geometry>
        </visual>
      </link>
      <plugin name="random" filename="libRandomVelocityPlugin.so">
        <link>link</link>
        <initial_velocity>0.5 0.0 0</initial_velocity>
        <velocity_factor>0.2</velocity_factor>
        <update_period>5</update_period>
        <min_z>-5</min_z>
        <max_z>0</max_z>
      </plugin>
    </model>
</sdf>
