# 아두이노 FPS 컨트롤러 (Arduino FPS Controller)

## 프로젝트 정보

### 목적 

아두이노와 에어건, 자이로스코프, 조이스틱 등의 센서를 활용하여 FPS 게임에서 활용 가능한 에어 마우스 컨트롤러를 제작한다.

### 개발 기간

<ul>
    <li> 2023년 7월 개인 스터디 진행
    <li> 2023년 8월 아이디어 회의 진행
    <li> 2023년 9월 LED, 스위치를 활용한 아두이노 스터디 진행
    <li> 2023년 10월 컨트롤러 기능 개발 시작
    <li> 2023년 11월 실물 컨트롤러 제작 및 기능 구현 테스트
    <li> 2023년 12월 인터페이스 프로그래밍 전시회 진행 
        <br>(11월 30일(목) ~ 12월 1일(금))
</ul>

### 팀 소개
아두이노 컨트롤러 개발 팀 - FPS 컨트롤러

<ul>
    <li> 세종대학교 전자정보통신공학과 박상욱 - 개발 + 제작
    <li> 세종대학교 전자정보통신공학과 문창민 - 제작
    <li> 세종대학교 전자정보통신공학과 정유철 - 개발
    <li> 세종대학교 기계공학과 문아영 - 개발
    <li> 세종대학교 전자정보통신공학과 황세진 - 개발
</ul>

### 기술 스택 및 사용 센서
![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)

- 아두이노 Leonardo
- 자이로스코프 (MPU6050)
- 진동 센서
- 택트
- 조이스틱

### 개발 기능
- 아두이로 레오나르도 활용하여 마우스 및 키보드 제어
- 에어건 총구에 부착된 자이로스코프를 활용하여 에어 마우스 구현
- 전방 손잡이에 부착된 조이스틱을 이용하여 WASD 이동 지원
- 방아쇠와 장전 손잡이에 부착된 버튼을 활용하여 해당 키 입력
- 후방 손압이에 진동 센서를 이용하여 격발 시 사용자에 진동 햅틱 제공
- 왼쪽 몸통에 부착된 조이스틱을 이용하여 줌 on/off 및 조절 지원

### 컨트롤러 실물 및 시연 이미지

#### 회로도
<img src = "https://github.com/Arduino-Controller/FPS-Controller/blob/main/images/circuit.png?raw=true" width=500>

#### 에어건 센서 부착 위치 및 디자인
<img src = "https://github.com/Arduino-Controller/FPS-Controller/blob/main/images/design.png?raw=true" width=500>

#### FPS 컨트롤러 실물
<img src = "https://github.com/Arduino-Controller/FPS-Controller/blob/main/images/gun1.jpg?raw=true" width=500>
<img src = "https://github.com/Arduino-Controller/FPS-Controller/blob/main/images/gun2.jpg?raw=true" width=500>

#### 프로그래밍 전시회 시연
<img src = "https://github.com/Arduino-Controller/FPS-Controller/blob/main/images/display.jpg?raw=true" width=500>

### 컨트롤러 시연 영상 추후 추가 예정
<a href="https://www.youtube.com/watch?v=qWnTnSh8Dt8">
    <img src = "https://github.com/Arduino-Controller/FPS-Controller/blob/main/images/FPS_시연.jpg?raw=true" width=500>
</a>

### 참고 사이트
1. 온라인 아두이노 시뮬레이터 (회로도 제작)<br>
https://wokwi.com/projects/new/arduino-uno
2. 에어 마우스 코드 참고 블로그<br>
https://jinho-study.tistory.com/248
