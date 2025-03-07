project(GameLib)

set(SOURCE_FILES pch.h
        GameView.cpp
        GameView.h
        Pin.cpp
        Pin.h
        VisitorBase.cpp
        VisitorBase.h
        MainFrame.cpp
        MainFrame.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        ids.h
        Scoreboard.cpp
        Scoreboard.h
        Sensor.cpp
        Sensor.h
        SensorOutput.cpp
        SensorOutput.h
        Beam.cpp
        Beam.h
        Sparty.cpp
        Sparty.h
        Gate.cpp
        Gate.h
        GateOr.cpp
        GateOr.h
        GateAnd.cpp
        GateAnd.h
        GateNot.cpp
        GateNot.h
        GateSRFlipFlop.cpp
        GateSRFlipFlop.h
        GateDFlipFlop.cpp
        GateDFlipFlop.h
        Conveyor.cpp
        Conveyor.h
        Product.cpp
        Product.h
        Level.cpp
        Level.h
        Scoreboard.cpp
        Scoreboard.h
        IDraggable.cpp
        IDraggable.h
        ItemFactory.cpp
        ItemFactory.h
        ItemFinder.h
        SpartyPin.cpp
        SpartyPin.h
        ItemFinder.cpp
        OutputSetter.cpp
        OutputSetter.h
        OutputResetter.cpp
        OutputResetter.h
        PinVisitor.cpp
        PinVisitor.h
        BeamVisitor.cpp
        BeamVisitor.h
        SensorOutputVisitor.cpp
        SensorOutputVisitor.h
        ProductDetector.cpp
        ProductDetector.h
        LastProductVisitor.cpp
        LastProductVisitor.h
        ScoreboardVisitor.cpp
        ScoreboardVisitor.h
        TopologicalSortVisitor.h
        TopologicalSortVisitor.cpp
)


set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)