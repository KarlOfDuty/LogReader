pipeline {
  agent any
  stages {
    stage('Dependencies') {
      steps {
        echo 'No dependencies for now'
      }
    }
    stage('Build') {
      steps {
        sh 'cmake .'
        sh 'make'
      }
    }
    stage('Archive') {
      steps {
        archiveArtifacts 'LogReader'
      }
    }
  }
}
