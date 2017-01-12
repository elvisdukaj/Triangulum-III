/* globals __DEV__ */
import Phaser from 'phaser'
import Player from '../player.js'

import Handy from '../handy.js'

export default class extends Phaser.State {
  init(connection, id) {
    this.connection = connection;
    this.playerId = id;
  }
  preload() {}
  create() {
    console.log("Game create");

    // add brackground
    this.game.add.tileSprite(0, 0, this.game.world.width, this.game.world.height, 'starfield');

    // simple Physics
    this.game.physics.startSystem(Phaser.Physics.ARCADE);

    // player
    this.player = new Player(this.game);
    this.game.add.existing(this.player);
    this.game.camera.follow(this.player);

    this.cursors = this.game.input.keyboard.createCursorKeys();
  }
  update() {
    if (this.socket.readyState != 1)
      return;

    // get world updates from the server
    //

    // Gather inputs to json
    var input = {
      left: this.cursors.left.isDown ? 1 : 0,
      right: this.cursors.right.isDown ? 1 : 0,
      up: this.cursors.up.isDown ? 1 : 0,
      down: this.cursors.down.isDown ? 1 : 0,
      fire: 0
    }

    // Only send if input changed
    if ( this.lastInput && !Handy.equalJson(input, this.lastInput))
      this.socket.send(JSON.stringify(input))

    this.lastInput = input
  }
}
