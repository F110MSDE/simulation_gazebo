# simulation_gazebo
SNUST MSDE f1_tenth simulation setting with gazebo  
서울과학기술대학교 MSDE F1/10 Gazebo Simulation setup

## 1. 설치
ROS-kinetic in ubuntu 16.04  
Gazebo

### 1.1. ros gazebo 패키지 설치하기

```bash
$ sudo apt-get install ros-kinetic-gazebo-ros-pkgs ros-kinetic-gazebo-ros-control
```


### 1.2. simulation workspace 만들기

```bash
$ cd
~$ mkdir -p simulation_ws/src
```


### 1.3. Clone repo

```bash
$ cd ~/simulation_ws/src
~/simulation_ws/src $ git clone https://github.com/F110MSDE/simulation_gazebo.git
```

### 1.4. workspace 초기화하고, 빌드하기

```bash
~/simulation_ws/src $ catkin_init_workspace
~/simulation_ws/src $ cd ..
~/simulation_ws $ catkin_make install
```

### 1.5. bashrc 수정

bashrc 파일에 simulation_ws setup.bash source 추가해주기  
~/.bashrc 파일을 열어
```bash
$ gedit ~/.bashrc
```
아래 명령어 추가
```bash
source ~/.simulation_ws/devel/setup.bash
```
저장후 모든 terminal 닫았다가 열거나, source bashrc 해주기
```bash
$ source ~/.bashrc
```
