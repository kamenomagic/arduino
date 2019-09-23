import React from 'react';
import axios from 'axios'
import styles from './synchrobot.module.css'
import Slider from '@material-ui/core/Slider';

class SynchroSlider extends React.Component {
  constructor(props) {
    super(props)
    this.handleSlider = this.handleSlider.bind(this)
    this.state = {id: props.id, value: 90}
  }

  handleSlider(id, value) {
    axios.post('http://localhost:4567/move', {command: `${id}${value}`})
    this.setState({value})
  }

  render() {
    return (
      <div className={styles.slider}>
        <h1>{this.state.id}: {this.state.value}</h1>
        <Slider
          onChangeCommitted={(e, val) => this.handleSlider(this.state.id, val)}
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
    )
  }
}

export default class Synchrobot extends React.Component {
  render() {
    return (
      <div className={styles.synchrobot}>
        <h1 className={styles.title}>Synchrobot</h1>
        <div className={styles.sliderContainer}>
          <div className={styles.sliderItem}>
            <div className={styles.sliderInnerItem}>
              <SynchroSlider id='a'/>
              <SynchroSlider id='b'/>
              <SynchroSlider id='c'/>
            </div>
            <div className={styles.sliderInnerItem}>
              <SynchroSlider id='f'/>
              <SynchroSlider id='e'/>
              <SynchroSlider id='d'/>
            </div>
          </div>
          <div className={styles.sliderItem}>
            <div className={styles.sliderInnerItem}>
              <SynchroSlider id='j'/>
              <SynchroSlider id='k'/>
              <SynchroSlider id='l'/>
            </div>
            <div className={styles.sliderInnerItem}>
              <SynchroSlider id='i'/>
              <SynchroSlider id='h'/>
              <SynchroSlider id='g'/>
            </div>
          </div>
        </div>
      </div>
    )
  }
}
