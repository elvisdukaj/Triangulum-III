import 'pixi'
import 'p2'
import Phaser from 'phaser'

import BootState from './states/Boot'
import SplashState from './states/Splash'
import MainMenuState from './states/MainMenu'
import GameState from './states/Game'

class Game extends Phaser.Game {

    constructor() {
        let width = document.documentElement.clientWidth > 960 ? 960 : document.documentElement.clientWidth
        let height = document.documentElement.clientHeight > 540 ? 540 : document.documentElement.clientHeight

        super(width, height, Phaser.AUTO, 'content', null)

        this.state.add('Boot', BootState, false)
        this.state.add('Splash', SplashState, false)
        this.state.add('MainMenu', MainMenuState, false)
        this.state.add('Game', GameState, false)

        this.state.start('Boot')
    }
}

window.game = new Game()