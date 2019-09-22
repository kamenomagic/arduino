import React from 'react';
import axios from 'axios'
import styles from './synchrobot.module.css'
import Slider from '@material-ui/core/Slider';

export default class Synchrobot extends React.Component {
  constructor(props) {
    super(props)
    this.handleSlider = this.handleSlider.bind(this)
  }

  handleSlider(event, value) {
    console.log(value)
    axios.post('http://localhost:4567/move', {command: `a${value}`})
  }

  render() {
    return (
      <div className={styles.synchrobot}>
        <h1>Synchrobot</h1>
        <div className={styles.slider}>
          <h1>A</h1>
          <Slider
            onChangeCommitted={(e, val) => this.handleSlider(e, val)}
            orientation="vertical"
            defaultValue={90}
            aria-labelledby="discrete-slider"
            valueLabelDisplay="auto"
            step={5}
            marks
            min={0}
            max={180}
          />
        </div>
      </div>
    )
  }
}
