
"use strict";

let NodeStatus = require('./NodeStatus.js');
let Latency = require('./Latency.js');
let ProcessStatus = require('./ProcessStatus.js');
let NodeList = require('./NodeList.js');
let FlightEvent = require('./FlightEvent.js');
let Keypoint = require('./Keypoint.js');
let Detection = require('./Detection.js');
let WaypointList = require('./WaypointList.js');
let ControlMessage = require('./ControlMessage.js');
let TelemString = require('./TelemString.js');
let Box = require('./Box.js');
let FlightCommand = require('./FlightCommand.js');
let ImageDetections = require('./ImageDetections.js');
let FlightStateTransition = require('./FlightStateTransition.js');
let ImageSegmentation = require('./ImageSegmentation.js');
let JoyDef = require('./JoyDef.js');

module.exports = {
  NodeStatus: NodeStatus,
  Latency: Latency,
  ProcessStatus: ProcessStatus,
  NodeList: NodeList,
  FlightEvent: FlightEvent,
  Keypoint: Keypoint,
  Detection: Detection,
  WaypointList: WaypointList,
  ControlMessage: ControlMessage,
  TelemString: TelemString,
  Box: Box,
  FlightCommand: FlightCommand,
  ImageDetections: ImageDetections,
  FlightStateTransition: FlightStateTransition,
  ImageSegmentation: ImageSegmentation,
  JoyDef: JoyDef,
};
