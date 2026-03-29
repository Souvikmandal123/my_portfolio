(function () {
  'use strict';

  angular.module('portfolioApp', []).controller('MainCtrl', [
    '$scope',
    '$http',
    '$document',
    function ($scope, $http, $document) {
      $scope.title = 'Portfolio';
      $scope.resumeUrl =
        'https://drive.google.com/file/d/1CE0d2_ZyD_Q-OS7p3_J4_ajSbr9mwmvk/view?usp=sharing';
      $scope.navOpen = false;
      $scope.contactStatus = 'idle';
      $scope.contact = {
        name: '',
        email: '',
        message: ''
      };

      $scope.projects = [
        {
          name: 'API platform',
          stack: 'Django · PostgreSQL',
          blurb: 'REST services with clear contracts and predictable deployments.'
        },
        {
          name: 'Client dashboard',
          stack: 'AngularJS · JavaScript',
          blurb: 'Focused UI for monitoring metrics with fast, accessible layouts.'
        },
        {
          name: 'Automation toolkit',
          stack: 'Python · CI',
          blurb: 'Scripts and pipelines that keep releases boring—in a good way.'
        }
      ];

      $scope.toggleNav = function () {
        $scope.navOpen = !$scope.navOpen;
      };

      $scope.scrollTo = function (id, $event) {
        if ($event) {
          $event.preventDefault();
        }
        $scope.navOpen = false;
        var el = document.getElementById(id);
        if (el) {
          el.scrollIntoView({ behavior: 'smooth', block: 'start' });
        }
      };

      var onKeydown = function (e) {
        if (e.key === 'Escape') {
          $scope.$apply(function () {
            $scope.navOpen = false;
          });
        }
      };
      $document.on('keydown', onKeydown);
      $scope.$on('$destroy', function () {
        $document.off('keydown', onKeydown);
      });

      $scope.submitContact = function () {
        if (!$scope.contact.name || !$scope.contact.email || !$scope.contact.message) {
          return;
        }
        if ($scope.contactStatus === 'sending') {
          return;
        }
        $scope.contactStatus = 'sending';
        $http
          .post(
            '/api/contact/',
            {
              name: $scope.contact.name,
              email: $scope.contact.email,
              message: $scope.contact.message
            },
            { headers: { 'Content-Type': 'application/json' } }
          )
          .then(function (res) {
            if (res.data && res.data.ok) {
              $scope.contactStatus = 'ok';
              $scope.contact = { name: '', email: '', message: '' };
            } else {
              $scope.contactStatus = 'error';
            }
          })
          .catch(function () {
            $scope.contactStatus = 'error';
          });
      };
    }
  ]);
})();
