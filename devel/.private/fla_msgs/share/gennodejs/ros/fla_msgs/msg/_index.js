
"use strict";

let ImageDetections = require('./ImageDetections.js');
let ProcessStatus = require('./ProcessStatus.js');
let Detection = require('./Detection.js');
let NodeList = require('./NodeList.js');
let FlightEvent = require('./FlightEvent.js');
let JoyDef = require('./JoyDef.js');
let ImageSegmentation = require('./ImageSegmentation.js');
let Keypoint = require('./Keypoint.js');
let FlightStateTransition = require('./FlightStateTransition.js');
let NodeStatus = require('./NodeStatus.js');
let Box = require('./Box.js');
let TelemString = require('./TelemString.js');
let FlightCommand = require('./FlightCommand.js');
let ControlMessage = require('./ControlMessage.js');
let WaypointList = require('./WaypointList.js');
let Latency = require('./Latency.js');

module.exports = {
  ImageDetections: ImageDetections,
  ProcessStatus: ProcessStatus,
  Detection: Detection,
  NodeList: NodeList,
  FlightEvent: FlightEvent,
  JoyDef: JoyDef,
  ImageSegmentation: ImageSegmentation,
  Keypoint: Keypoint,
  FlightStateTransition: FlightStateTransition,
  NodeStatus: NodeStatus,
  Box: Box,
  TelemString: TelemString,
  FlightCommand: FlightCommand,
  ControlMessage: ControlMessage,
  WaypointList: WaypointList,
  Latency: Latency,
};
